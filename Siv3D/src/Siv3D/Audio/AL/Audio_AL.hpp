//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>

# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <unistd.h>

# if defined(SIV3D_TARGET_MACOS)

	# include <OpenAL/al.h>
	# include <OpenAL/alc.h>

# elif defined(SIV3D_TARGET_LINUX)

	# include <AL/al.h>
	# include <AL/alc.h>

# endif

# include "../AudioControlManager.hpp"
# include <Siv3D/Optional.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	class SimpleVoice_AL
	{
	private:
		
		const Wave* m_pWave = nullptr;
		
		ALuint m_source = 0;
		
		
		bool m_isActive = false;
		
		bool m_isPaused = false;
		
		bool m_isEnd = false;
		

		std::thread m_thread;
		
		std::atomic<bool> m_abort = false;
		
		
		static constexpr size_t BufferSamples = 2048;
		
		Array<WaveSampleS16> m_tmpBuffer;
		
		size_t m_freeBuffer = 2;
		
		std::atomic<size_t> m_readPos = 0;
		
		std::array<ALuint, 2> m_buffers = {{ 0, 0 }};
		
		size_t m_currentBufferID = 0;
		
		
		void feedDetailNonLoop()
		{
			const size_t samplesLeft = m_pWave->size() - m_readPos;
			
			if (samplesLeft == 0)
			{
				return;
			}
			
			const size_t samplesToFeed = std::min(samplesLeft, m_tmpBuffer.size());
			
			for (size_t i = 0; i < samplesToFeed; ++i)
			{
				const WaveSample& src = (*m_pWave)[m_readPos + i];
				
				m_tmpBuffer[i] = src.asS16();
			}
			
			m_readPos += samplesToFeed;
			
			const size_t samplesWritten = samplesToFeed;
			
			::alBufferData(m_buffers[m_currentBufferID], AL_FORMAT_STEREO16, m_tmpBuffer.data(),
						   static_cast<ALsizei>(samplesWritten * sizeof(WaveSampleS16)), m_pWave->samplingRate());
			
			::alSourceQueueBuffers(m_source, 1, &m_buffers[m_currentBufferID]);
			
			++m_currentBufferID %= 2;
			
			--m_freeBuffer;
			
			//LOG_DEBUG(U"feed {} samples, pos: {}"_fmt(samplesToFeed, m_readPos));
		}
		
		void feed()
		{
			if (m_freeBuffer > 0)
			{
				feedDetailNonLoop();
			}
			
			ALint processed = 0;
			::alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);
			
			while (processed--)
			{
				ALuint buffer = 0;
				
				::alSourceUnqueueBuffers(m_source, 1, &buffer);
				
				++m_freeBuffer;
				
				feedDetailNonLoop();
			}
		}
		
		void onStreamEnd()
		{
			m_isActive = false;
			m_isPaused = false;
			m_isEnd = true;
			
			m_readPos  = 0;
			
			//LOG_TEST(U"End of Stream");
		}
		
		void onUpdate()
		{
			for (;;)
			{
				if (!m_source)
				{
					continue;
				}
				
				if (m_isActive)
				{
					feed();
					
					ALint sampleOffset = 0;
					::alGetSourcei(m_source, AL_SAMPLE_OFFSET, &sampleOffset);
				}
				
				ALint currentState = 0;
				::alGetSourcei(m_source, AL_SOURCE_STATE, &currentState);
				
				if (!m_isEnd && m_isActive && currentState == AL_STOPPED)
				{
					onStreamEnd();
				}
				
				if (m_abort)
				{
					break;
				}
				
				::usleep(5 * 1000);
			}
		}
		
	public:
		
		SimpleVoice_AL() = default;
		
		SimpleVoice_AL(const Wave& wave, const double volume, const double pitch)
			: m_pWave(&wave)
			, m_tmpBuffer(BufferSamples)
		{
			::alGenBuffers(2, m_buffers.data());
			::alGenSources(1, &m_source);
			
			::alSourcef(m_source, AL_GAIN, static_cast<float>(volume));
			::alSourcef(m_source, AL_PITCH, static_cast<float>(pitch));
			
			::alSource3f(m_source, AL_POSITION, 0, 0, 0);
			::alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
			::alSourcei(m_source, AL_LOOPING, AL_FALSE);
			
			feed();

			m_thread = std::thread(&SimpleVoice_AL::onUpdate, this);

			::alSourcePlay(m_source);
			
			m_isActive = true;
			m_isPaused = false;
		}
		
		~SimpleVoice_AL()
		{
			if (!m_abort)
			{
				m_abort = true;
			}
			
			if (m_thread.joinable())
			{
				m_thread.join();
			}
			
			if (m_source)
			{
				::alSourceStop(m_source);
				
				::alDeleteSources(1, &m_source);
			}
			
			if (m_buffers[0])
			{
				::alDeleteBuffers(2, &m_buffers[0]);
			}
		}
	};
	
	class VoiceStream_AL
	{
	private:
		
		const Wave* m_pWave = nullptr;
		
		ALuint m_source = 0;
		
		
		Optional<AudioLoopTiming> m_loop;
		
		std::pair<double, double> m_volume = { 1.0, 1.0 };
		
		double m_speed = 1.0;
		

		bool m_isActive = false;
		
		bool m_isPaused = false;
		
		bool m_isEnd = false;
		
		
		std::thread m_thread;
		
		bool m_hasThread = false;
		
		std::atomic<bool> m_abort = false;
		
		
		std::atomic<int64> m_posSampleCurrentStream = 0;
		
		std::atomic<int64> m_samplesPlayedAccumulated = 0;
		
		std::atomic<size_t> m_posSmaplesAccumulated = 0;
		
		Array<size_t> m_samplesQueued;
		
		
		static constexpr size_t BufferSamples = 2048;
		
		Array<WaveSampleS16> m_tmpBuffer;
		
		size_t m_freeBuffer = 2;
		
		std::atomic<size_t> m_readPos = 0;
		
		std::array<ALuint, 2> m_buffers = {{ 0, 0 }};
		
		size_t m_currentBufferID = 0;
		
		
		void feedDetailNonLoop()
		{
			const size_t samplesLeft = m_pWave->size() - m_readPos;
			
			if (samplesLeft == 0)
			{
				return;
			}
			
			const size_t samplesToFeed = std::min(samplesLeft, m_tmpBuffer.size());
			
			for (size_t i = 0; i < samplesToFeed; ++i)
			{
				const WaveSample& src = (*m_pWave)[m_readPos + i];
				
				m_tmpBuffer[i] = src.asS16();
			}
			
			m_readPos += samplesToFeed;
			
			const size_t samplesWritten = samplesToFeed;
			
			::alBufferData(m_buffers[m_currentBufferID], AL_FORMAT_STEREO16, m_tmpBuffer.data(),
						   static_cast<ALsizei>(samplesWritten * sizeof(WaveSampleS16)), m_pWave->samplingRate());
			
			::alSourceQueueBuffers(m_source, 1, &m_buffers[m_currentBufferID]);
			
			m_samplesQueued << samplesWritten;
			
			++m_currentBufferID %= 2;
			
			--m_freeBuffer;
			
			//LOG_DEBUG(U"feed {} samples, pos: {}"_fmt(samplesToFeed, m_readPos));
		}
		
		void feedDetailLoop()
		{
			const size_t bufferSize = m_tmpBuffer.size();
			size_t samplesFed = 0;
			size_t tmpBufferPos = 0;
			
			while (samplesFed < bufferSize)
			{
				size_t samplesAvailable = m_loop->endPos - m_readPos;
				
				if (samplesAvailable == 0)
				{
					m_readPos = m_loop->beginPos;
					
					// [Siv3D ToDo] ループすると Audio::posSample() が Audio::streamPosSample() より大きくなる
					m_posSmaplesAccumulated = m_loop->beginPos;
					m_posSampleCurrentStream = 0;
					
					samplesAvailable = m_loop->endPos - m_loop->beginPos;
				}
				
				const size_t samplesToFeed = std::min(samplesAvailable, bufferSize - samplesFed);
				
				for (size_t i = 0; i < samplesToFeed; ++i)
				{
					const WaveSample& src = (*m_pWave)[m_readPos + i];
					
					m_tmpBuffer[tmpBufferPos++] = src.asS16();
				}
				
				samplesFed += samplesToFeed;
				m_readPos += samplesToFeed;
			}
			
			const size_t samplesWritten = samplesFed;
			
			::alBufferData(m_buffers[m_currentBufferID], AL_FORMAT_STEREO16, m_tmpBuffer.data(),
						   static_cast<ALsizei>(samplesWritten * sizeof(WaveSampleS16)), m_pWave->samplingRate());
			
			::alSourceQueueBuffers(m_source, 1, &m_buffers[m_currentBufferID]);
			
			m_samplesQueued << samplesWritten;
			
			++m_currentBufferID %= 2;
			
			--m_freeBuffer;
			
			//LOG_DEBUG(U"feed {} samples, pos: {}"_fmt(samplesFed, m_readPos));
		}
		
		void feed()
		{
			if (m_freeBuffer > 0)
			{
				if (m_loop)
				{
					feedDetailLoop();
				}
				else
				{
					feedDetailNonLoop();
				}
			}
			
			ALint processed = 0;
			::alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);
			
			while (processed--)
			{
				ALuint buffer = 0;
				
				::alSourceUnqueueBuffers(m_source, 1, &buffer);
				
				m_posSmaplesAccumulated += m_samplesQueued.front();
				
				m_samplesPlayedAccumulated += m_samplesQueued.front();
				
				m_samplesQueued.pop_front();
				
				++m_freeBuffer;
				
				if (m_loop)
				{
					feedDetailLoop();
				}
				else
				{
					feedDetailNonLoop();
				}
			}
		}
		
		void onStreamEnd()
		{
			m_isActive = false;
			m_isPaused = false;
			m_isEnd = true;
			
			m_readPos  = 0;
			m_posSmaplesAccumulated = 0;
			m_samplesPlayedAccumulated = 0;
			m_posSampleCurrentStream = 0;

			m_volume = { 1.0, 1.0 };
			m_speed = 1.0;
			
			//LOG_TEST(U"End of Stream");
		}
		
		void onUpdate()
		{
			for (;;)
			{
				if (!m_source)
				{
					continue;
				}
				
				if (m_isActive)
				{
					feed();
					
					ALint sampleOffset = 0;
					::alGetSourcei(m_source, AL_SAMPLE_OFFSET, &sampleOffset);
					m_posSampleCurrentStream = sampleOffset;
				}
	
				ALint currentState = 0;
				::alGetSourcei(m_source, AL_SOURCE_STATE, &currentState);
				
				if (!m_isEnd && m_isActive && currentState == AL_STOPPED)
				{
					onStreamEnd();
				}
				
				if (m_abort)
				{
					break;
				}

				::usleep(5 * 1000);
			}
		}
		
		void updateVolume()
		{
			// [Siv3D ToDo]
			const float volume = static_cast<float>((m_volume.first + m_volume.second) * 0.5);
			
			::alSourcef(m_source, AL_GAIN, volume);
		}
		
		void updateSpeed()
		{
			::alSourcef(m_source, AL_PITCH, static_cast<float>(m_speed));
		}
		
	public:
		
		VoiceStream_AL() = default;
		
		VoiceStream_AL(const Wave& wave)
			: m_pWave(&wave)
			, m_tmpBuffer(BufferSamples)
		{
			::alGenBuffers(2, m_buffers.data());
			::alGenSources(1, &m_source);
			
			::alSourcef(m_source, AL_GAIN, 1.0);
			::alSourcef(m_source, AL_PITCH, 1.0);
			
			::alSource3f(m_source, AL_POSITION, 0, 0, 0);
			::alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
			::alSourcei(m_source, AL_LOOPING, AL_FALSE);
		}
		
		~VoiceStream_AL()
		{
			if (!m_abort)
			{
				m_abort = true;
			}
			
			if (m_thread.joinable())
			{
				m_thread.join();
			}
			
			if (m_source)
			{
				::alSourceStop(m_source);
				
				::alDeleteSources(1, &m_source);
			}
			
			if (m_buffers[0])
			{
				::alDeleteBuffers(2, &m_buffers[0]);
			}
		}
		
		bool isPlaying() const
		{
			return m_isActive && !m_isPaused;
		}
		
		bool isPaused() const
		{
			return m_isPaused;
		}
		
		int64 streamPosSample() const
		{
			return m_readPos;
		}
		
		int64 getPosSample() const
		{
			return m_posSmaplesAccumulated + m_posSampleCurrentStream;
		}
		
		int64 samplesPlayed() const
		{
			return m_samplesPlayedAccumulated + m_posSampleCurrentStream;
		}
		
		void setVolume(const std::pair<double, double>& volume)
		{
			if (volume == m_volume)
			{
				return;
			}
			
			m_volume = volume;
			
			updateVolume();
		}
		
		const std::pair<double, double> getVolume() const
		{
			return m_volume;
		}
		
		void setSpeed(const double speed)
		{
			const double newSpeed = Clamp<double>(speed, 1.0 / 1024.0, 2.0);
			
			if (newSpeed == m_speed)
			{
				return;
			}
			
			m_speed = newSpeed;
			
			updateSpeed();
		}
		
		double getSpeed() const
		{
			return m_speed;
		}
		
		void setLoop(const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
		{
			if (!loop)
			{
				m_loop.reset();
			}
			else
			{
				m_loop.emplace(loopBeginSample, loopEndSample);
			}
			
			stop();
		}
		
		const Optional<AudioLoopTiming>& getLoop() const
		{
			return m_loop;
		}
		
		bool play()
		{
			if (m_isActive && !m_isPaused)
			{
				return true;
			}
			
			feed();
			
			if (!m_hasThread)
			{
				m_thread = std::thread(&VoiceStream_AL::onUpdate, this);
				
				m_hasThread = true;
			}

			::alSourcePlay(m_source);
			
			m_isActive = true;
			m_isPaused = false;
			m_isEnd = false;
			
			return true;
		}
		
		void pause()
		{
			if (!m_isActive)
			{
				return;
			}
			
			::alSourcePause(m_source);
			
			m_isPaused = true;
		}
		
		void stop()
		{
			if (!m_isActive)
			{
				return;
			}
			
			::alSourceStop(m_source);
			
			//m_isActive = false;
			//m_isPaused = false;
		}
		
		bool reachedEnd() const
		{
			return m_isEnd;
		}
	};
	
	class Audio_AL
	{
	private:
	
		Wave m_wave;
		
		bool m_initialized = false;
		
		VoiceStream_AL m_stream;
		
		static constexpr size_t MaxVoiceShots = 32;
		
		Array<std::shared_ptr<SimpleVoice_AL>> m_voiceShots;
		
	public:
		
		Audio_AL() = default;
		
		Audio_AL(Wave&& wave)
			: m_wave(std::move(wave))
			, m_stream(m_wave)
		{
			m_initialized = true;
			
			m_voiceShots.reserve(MaxVoiceShots);
		}
		
		~Audio_AL()
		{
			m_voiceShots.clear();
		}
		
		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		const Wave& getWave() const
		{
			return m_wave;
		}
		
		VoiceStream_AL& getStream()
		{
			return m_stream;
		}
		
		const VoiceStream_AL& getStream() const
		{
			return m_stream;
		}
		
		void playOneShot(const double volume, const double pitch)
		{
			if (m_voiceShots.size() + 1 >= MaxVoiceShots)
			{
				m_voiceShots.pop_front();
			}
			
			m_voiceShots.push_back(std::make_shared<SimpleVoice_AL>(m_wave, volume, pitch));
		}
		
		void stopAllShots()
		{
			m_voiceShots.clear();
		}
	};
}

# endif
