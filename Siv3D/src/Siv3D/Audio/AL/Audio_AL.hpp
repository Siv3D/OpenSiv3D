//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

# include <Siv3D/Wave.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	enum class AudioControlState
	{
		Paused,
		
		Playing,
		
		Stopped,
	};
	
	class VoiceStream_AL
	{
	private:
		
	public:
		
	};
	
	class Audio_AL
	{
	private:
	
		Wave m_wave;
		
		bool m_initialized = false;
		
		ALuint m_source = 0;
		
		std::atomic<AudioControlState> m_state = AudioControlState::Paused;
		
		bool m_isActive = false;
		
		bool m_isPaused = false;
		
		
		std::thread m_thread;
		
		bool m_hasThread = false;
		
		
		std::atomic<bool> m_abort = false;
		
		std::atomic<int64> m_posSampleCurrentStream = 0;
		
		std::atomic<int64> m_samplesPlayedAccumulated = 0;
		
		
		static constexpr size_t BufferSamples = 2048;
		
		std::array<WaveSampleS16, BufferSamples> m_tmpBuffer;
		
		size_t m_freeBuffer = 2;
		
		std::atomic<size_t> m_readPos = 0;
		
		std::atomic<size_t> m_posSmaplesAccumulated = 0;
		
		Array<size_t> m_samplesQueued;
		
		std::array<ALuint, 2> m_buffers = {{ 0, 0 }};
		
		size_t m_currentBufferID = 0;
		
		
		void feedDetail()
		{
			const size_t samplesLeft = m_wave.size() - m_readPos;
			
			if (samplesLeft == 0)
			{
				return;
			}
			
			const size_t samplesToFeed = std::min(samplesLeft, m_tmpBuffer.size());
			
			for (size_t i = 0; i < samplesToFeed; ++i)
			{
				const WaveSample& src = m_wave[m_readPos + i];
				
				m_tmpBuffer[i] = src.asS16();
			}
			
			m_readPos += samplesToFeed;
			
			const size_t samplesWritten = samplesToFeed;
			
			::alBufferData(m_buffers[m_currentBufferID], AL_FORMAT_STEREO16, m_tmpBuffer.data(),
						   static_cast<ALsizei>(samplesWritten * sizeof(WaveSampleS16)), m_wave.samplingRate());
			
			::alSourceQueueBuffers(m_source, 1, &m_buffers[m_currentBufferID]);
			
			m_samplesQueued << samplesWritten;
			
			++m_currentBufferID %= 2;
			
			--m_freeBuffer;
			
			//LOG_DEBUG(U"feed {} samples, pos: {}"_fmt(samplesToFeed, m_readPos));
		}
		
		void feed()
		{
			if (m_freeBuffer > 0)
			{
				feedDetail();
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
				
				feedDetail();
			}
		}
		
		void onUpdate()
		{
			for (;;)
			{
				if (!m_source)
				{
					continue;
				}
				
				if (m_state == AudioControlState::Playing)
				{
					feed();
				}
				
				ALint sampleOffset = 0;
				::alGetSourcei(m_source, AL_SAMPLE_OFFSET, &sampleOffset);
				m_posSampleCurrentStream = sampleOffset;
				
				ALint currentState = 0;
				::alGetSourcei(m_source, AL_SOURCE_STATE, &currentState);
				
				if (m_isActive && currentState == AL_STOPPED)
				{
					m_isActive = false;
					m_isPaused = false;
					m_readPos  = 0;
					m_posSmaplesAccumulated = 0;
					m_samplesPlayedAccumulated = 0;
					m_state = AudioControlState::Stopped;
					
					LOG_TEST(U"End of Stream");
				}
				
				if (m_abort)
				{
					break;
				}
				
				switch (m_state)
				{
					case AudioControlState::Paused:
					{
						if (m_isActive && !m_isPaused)
						{
							::alSourcePause(m_source);
							
							m_isPaused = true;
						}
						
						break;
					}
					case AudioControlState::Playing:
					{
						if (!m_isActive || m_isPaused)
						{
							feed();
							
							::alSourcePlay(m_source);

							m_isActive = true;
							m_isPaused = false;
						}
						
						break;
					}
					case AudioControlState::Stopped:
					{
						if (m_isActive)
						{
							::alSourceStop(m_source);
							
							m_isActive = false;
							m_isPaused = false;
						}
						
						break;
					}
				}
				
				::usleep(5 * 1000);
			}
		}
		
	public:
		
		Audio_AL() = default;
		
		Audio_AL(Wave&& wave)
			: m_wave(std::move(wave))
		{
			::alListener3f(AL_POSITION, 0, 0, 1.0f);
			::alListener3f(AL_VELOCITY, 0, 0, 0);
			const ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
			::alListenerfv(AL_ORIENTATION, listenerOri);
			
			::alGenBuffers(2, m_buffers.data());
			
			::alGenSources(1, &m_source);
			::alSourcef(m_source, AL_PITCH, 1.0);
			::alSourcef(m_source, AL_GAIN, 1.0);
			::alSource3f(m_source, AL_POSITION, 0, 0, 0);
			::alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
			::alSourcei(m_source, AL_LOOPING, AL_FALSE);

			m_initialized = true;
		}
		
		~Audio_AL()
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
		
		bool isInitialized() const noexcept
		{
			return m_initialized;
		}
	
		void changeState(const AudioControlState state)
		{
			if (!m_source)
			{
				return;
			}
			
			m_state = state;
			
			if (!m_hasThread)
			{
				m_thread = std::thread(&Audio_AL::onUpdate, this);
				
				m_hasThread = true;
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
		
		uint32 samplingRate() const
		{
			return m_wave.samplingRate();
		}
		
		size_t samples() const
		{
			return m_wave.size();
		}
		
		void setLoop(const bool loop)
		{
			::alSourcei(m_source, AL_LOOPING, loop);
		}
		
		const Wave& getWave() const
		{
			return m_wave;
		}
	};
}

# endif
