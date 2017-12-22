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

# include "../IAudio.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	enum class AudioControlState
	{
		Paused,
		
		Playing,
		
		Stopped,
	};
	
	class Audio_AL
	{
	private:
	
		Wave m_wave;
		
		bool m_initialized = false;
		
		ALuint m_bufferID = 0;
		
		ALuint m_source = 0;
		
		std::atomic<AudioControlState> m_state = AudioControlState::Paused;
		
		bool m_isActive = false;
		
		bool m_isPaused = false;
		
		std::thread m_thread;
		
		std::atomic<bool> m_abort = false;
		
		std::atomic<int64> m_posSample = 0;
		
		void onUpdate()
		{
			for (;;)
			{
				::usleep(10 * 1000);
				
				if (!m_source)
				{
					continue;
				}
				
				ALint sampleOffset = 0;
				::alGetSourcei(m_source, AL_SAMPLE_OFFSET, &sampleOffset);
				m_posSample = sampleOffset;
				
				ALint currentState = 0;
				alGetSourcei(m_source, AL_SOURCE_STATE, &currentState);
				
				if (m_isActive && currentState == AL_STOPPED)
				{
					m_isActive = false;
					m_isPaused = false;
					m_state = AudioControlState::Stopped;
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
			
			::alGenBuffers(1, &m_bufferID);
			
			::alGenSources(1, &m_source);
			::alSourcef(m_source, AL_PITCH, 1.0);
			::alSourcef(m_source, AL_GAIN, 1.0);
			::alSource3f(m_source, AL_POSITION, 0, 0, 0);
			::alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
			::alSourcei(m_source, AL_LOOPING, AL_FALSE);

			Array<WaveSampleS16> buffer;
			buffer.reserve(m_wave.size());
			
			for (const auto& sample : m_wave)
			{
				buffer.push_back(sample.asS16());
			}
			
			::alBufferData(
						   m_bufferID,
						   AL_FORMAT_STEREO16,
						   buffer.data(),
						   static_cast<ALsizei>(buffer.size_bytes()),
						   wave.samplingRate());
			
			::alSourcei(m_source, AL_BUFFER, m_bufferID);
			
			m_initialized = true;
			
			m_thread = std::thread(&Audio_AL::onUpdate, this);
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
			
			if (m_bufferID)
			{
				::alDeleteBuffers(1, &m_bufferID);
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
		}
		
		bool isPlaying() const
		{
			return m_isActive && !m_isPaused;
		}
		
		bool isPaused() const
		{
			return m_isPaused;
		}
		
		int64 getPosSample() const
		{
			return m_posSample;
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
	
	
	class CAudio_AL : public ISiv3DAudio
	{
	private:
		
		ALCdevice* m_device = nullptr;
		
		ALCcontext* m_context = nullptr;
		
		AssetHandleManager<AudioID, Audio_AL> m_audios{ U"Audio" };

	public:

		CAudio_AL();

		~CAudio_AL() override;
		
		bool hasAudioDevice() const override;

		bool init() override;

		AudioID create(Wave&& wave) override;

		void release(AudioID handleID) override;

		uint32 samplingRate(AudioID handleID) override;

		size_t samples(AudioID handleID) override;

		void setLoop(AudioID handleID, bool loop, int64 loopBeginSample, int64 loopEndSample) override;

		bool play(AudioID handleID, const SecondsF& fadeinDuration) override;

		void pause(AudioID handleID, const SecondsF& fadeoutDuration) override;

		void stop(AudioID handleID, const SecondsF& fadeoutDuration) override;

		void playOneShot(AudioID handleID, double volume, double pitch) override;
		
		void stopAllShots(AudioID handleID) override;
		
		bool isPlaying(AudioID handleID) override;

		bool isPaused(AudioID handleID) override;

		uint64 posSample(AudioID handleID) override;

		uint64 streamPosSample(AudioID handleID) override;

		uint64 samplesPlayed(AudioID handleID) override;

		const Wave& getWave(AudioID handleID) override;

		void setVolume(AudioID handleID, const std::pair<double, double>& volume) override;

		std::pair<double, double> getVolume(AudioID handleID) override;

		void setSpeed(AudioID handleID, double speed) override;

		double getSpeed(AudioID handleID) override;

		std::pair<double, double> getMinMaxSpeed(AudioID handleID) override;

		bool updateFade() override;

		void fadeMasterVolume() override;
	};
}

# endif
