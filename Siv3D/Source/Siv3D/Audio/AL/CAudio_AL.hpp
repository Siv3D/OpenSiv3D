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

# include <OpenAL/al.h>
# include <OpenAL/alc.h>
# include "../IAudio.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class Audio_AL
	{
	private:
	
		Wave m_wave;
		
		bool m_initialized = false;
		
		ALuint m_bufferID = 0;
		
		ALuint m_source = 0;
		
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
			
			for(const auto& sample : m_wave)
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
		}
		
		~Audio_AL()
		{
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
		
		bool play()
		{
			if (!m_source)
			{
				return false;
			}
			
			::alSourcePlay(m_source);
			
			return true;
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
		
		AssetHandleManager<Audio::IDType, std::shared_ptr<Audio_AL>> m_audios{ S3DSTR("Audio") };

	public:

		CAudio_AL();

		~CAudio_AL() override;
		
		bool hasAudioDevice() const override;

		bool init() override;

		Audio::IDType create(Wave&& wave) override;

		void release(Audio::IDType handleID) override;

		uint32 samplingRate(Audio::IDType handleID) override;

		size_t samples(Audio::IDType handleID) override;

		void setLoop(Audio::IDType handleID, bool loop, int64 loopBeginSample, int64 loopEndSample) override;

		bool play(Audio::IDType handleID, const SecondsF& fadeinDuration) override;

		void pause(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		void stop(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		bool isPlaying(Audio::IDType handleID) override;

		bool isPaused(Audio::IDType handleID) override;

		uint64 posSample(Audio::IDType handleID) override;

		uint64 streamPosSample(Audio::IDType handleID) override;

		uint64 samplesPlayed(Audio::IDType handleID) override;

		const Wave& getWave(Audio::IDType handleID) override;

		void setVolume(Audio::IDType handleID, const std::pair<double, double>& volume) override;

		std::pair<double, double> getVolume(Audio::IDType handleID) override;

		void setSpeed(Audio::IDType handleID, double speed) override;

		double getSpeed(Audio::IDType handleID) override;

		std::pair<double, double> getMinMaxSpeed(Audio::IDType handleID) override;

		bool updateFade() override;

		void fadeMasterVolume() override;
	};
}

# endif
