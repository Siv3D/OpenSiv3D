//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/EngineLog.hpp>
# include "AudioData.hpp"
# include "AudioBus.hpp"
# include <ThirdParty/soloud/include/soloud_wav.h>
# include <ThirdParty/soloud/include/soloud_wavstream.h>
# include <ThirdParty/soloud/include/soloud_speech.h>
# include "DynamicAudioSource.hpp"

namespace s3d
{
	AudioData::AudioData(Null, SoLoud::Soloud* pSoloud)
		: m_pSoloud{ pSoloud }
	{
		// m_wave 準備
		{
			m_wave = Wave::Generate(SecondsF{ 0.5 }, [](double t) {
				return 0.5 * std::sin(t * Math::TwoPi) * std::sin(t * Math::TwoPi * 220.0 * (t * 4.0 + 1.0)); });
		
			m_wave.deinterleave();
		}

		std::unique_ptr<SoLoud::Wav> source = std::make_unique<SoLoud::Wav>();

		if (SoLoud::SO_NO_ERROR != source->loadRawWave(&m_wave[0].left,
			static_cast<uint32>(m_wave.size() * 2), static_cast<float>(m_wave.sampleRate()),
			2, false, false))
		{
			return;
		}

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);
		m_initialized	= true;
	}

	AudioData::AudioData(SoLoud::Soloud* pSoloud, Wave&& wave, const Optional<AudioLoopTiming>& loop)
		: m_pSoloud{ pSoloud }
		, m_loop{ loop.has_value() }
	{
		// m_wave 準備
		{
			m_wave = std::move(wave);

			if (loop && loop->endPos && (loop->endPos < m_wave.size()))
			{
				m_wave.resize(loop->endPos);
				m_wave.shrink_to_fit();
			}

			m_wave.deinterleave();
		}

		std::unique_ptr<SoLoud::Wav> source = std::make_unique<SoLoud::Wav>();

		if (SoLoud::SO_NO_ERROR != source->loadRawWave(&m_wave[0].left,
			static_cast<uint32>(m_wave.size() * 2), static_cast<float>(m_wave.sampleRate()),
			2, false, false))
		{
			return;
		}

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);

		if (loop)
		{
			m_loopTiming = *loop;
			m_audioSource->setLooping(true);
			m_audioSource->setLoopPoint(static_cast<double>(loop->beginPos) / m_sampleRate);
		}

		m_initialized	= true;
	}

	AudioData::AudioData(SoLoud::Soloud* pSoloud, const FilePathView path)
		: m_pSoloud{ pSoloud }
		, m_isStreaming{ true }
	{
		std::unique_ptr<SoLoud::WavStream> source = std::make_unique<SoLoud::WavStream>();

	# if SIV3D_PLATFORM(WINDOWS)
		
		if (FileSystem::IsResource(path))
		{
			m_resource = AudioResourceHolder{ path };

			if (SoLoud::SO_NO_ERROR != source->loadMem(
				static_cast<const unsigned char*>(m_resource.data()),
				static_cast<uint32>(m_resource.size()), false, false))
			{
				return;
			}
		}
		else
		{
			if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
			{
				return;
			}
		}

	# else
		
		if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
		{
			return;
		}

	# endif

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);
		m_initialized	= true;
	}

	AudioData::AudioData(SoLoud::Soloud* pSoloud, const FilePathView path, const uint64 loopBegin)
		: m_pSoloud{ pSoloud }
		, m_isStreaming{ true }
		, m_loop{ true }
	{
		std::unique_ptr<SoLoud::WavStream> source = std::make_unique<SoLoud::WavStream>();

	# if SIV3D_PLATFORM(WINDOWS)
		
		if (FileSystem::IsResource(path))
		{
			m_resource = AudioResourceHolder{ path };

			if (SoLoud::SO_NO_ERROR != source->loadMem(
				static_cast<const unsigned char*>(m_resource.data()),
				static_cast<uint32>(m_resource.size()), false, false))
			{
				return;
			}
		}
		else
		{
			if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
			{
				return;
			}
		}

	# else
		
		if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
		{
			return;
		}

	# endif

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);

		m_loopTiming	= { loopBegin, 0 };
		m_audioSource->setLooping(true);
		m_audioSource->setLoopPoint(static_cast<float>(static_cast<double>(loopBegin) / m_sampleRate));

		m_initialized	= true;
	}

	AudioData::AudioData(Dynamic, SoLoud::Soloud* pSoloud, const std::shared_ptr<IAudioStream>& pAudioStream, const Arg::sampleRate_<uint32> sampleRate)
		: m_pSoloud{ pSoloud }
		, m_isStreaming{ true }
	{
		std::unique_ptr<DynamicAudioSource> source = std::make_unique<DynamicAudioSource>(pAudioStream, *sampleRate);

		m_sampleRate = *sampleRate;
		m_lengthSample = (m_sampleRate * 1); // [Siv3D ToDo] この値は 0 にする？
		m_audioSource = std::move(source);

		m_initialized = true;
	}

	AudioData::AudioData(TextToSpeech, SoLoud::Soloud* pSoloud, const StringView text, const KlattTTSParameters& param)
		: m_pSoloud{ pSoloud }
	{
		std::unique_ptr<SoLoud::Speech> source = std::make_unique<SoLoud::Speech>();

		String input{ text };
		input.remove_if([](char32 c) { return (not IsASCII(c)); });

		if (SoLoud::SO_NO_ERROR != source->setText(input.toUTF8().c_str()))
		{
			return;
		}

		source->setParams(param.baseFrequency,
			static_cast<float>(param.baseSpeed),
			static_cast<float>(param.declination),
			KLATT_WAVEFORM(param.waveform));

		m_sampleRate = static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample = m_sampleRate;
		m_audioSource = std::move(source);
		m_initialized = true;
	}

	AudioData::~AudioData() {}

	bool AudioData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	uint32 AudioData::sampleRate() const noexcept
	{
		return m_sampleRate;
	}

	uint32 AudioData::samples() const noexcept
	{
		return m_lengthSample;
	}

	const AudioLoopTiming& AudioData::loopTiming() const noexcept
	{
		return m_loopTiming;
	}

	bool AudioData::isStreaming() const noexcept
	{
		return m_isStreaming;
	}

	int64 AudioData::samplesPlayed() const
	{
		if (not m_handle)
		{
			return 0;
		}

		return static_cast<int64>(m_pSoloud->getStreamTime(m_handle) * m_sampleRate);
	}
	
	bool AudioData::isActive() const
	{
		return m_pSoloud->isValidVoiceHandle(m_handle);
	}

	bool AudioData::isPlaying() const
	{
		if (not m_handle)
		{
			return false;
		}

		return (m_pSoloud->isValidVoiceHandle(m_handle)
			&& (m_pSoloud->getPause(m_handle) == false));
	}

	bool AudioData::isPaused() const
	{
		if (not m_handle)
		{
			return false;
		}

		return m_pSoloud->getPause(m_handle);
	}

	bool AudioData::isLoop() const
	{
		return m_loop;
	}

	void AudioData::setLoop(const bool loop)
	{
		if (loop == m_loop)
		{
			return;
		}

		m_audioSource->setLooping(loop);
		m_loop = loop;
	}
	
	void AudioData::setLoopPoint(const Duration& loopBegin)
	{
		m_audioSource->setLoopPoint(loopBegin.count());
		m_loopTiming.beginPos = static_cast<uint64>(loopBegin.count() / m_sampleRate);
	}

	void AudioData::play(const size_t busIndex)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle)) // 初回の再生
		{
			m_busIndex = static_cast<uint32>(busIndex);

			m_handle = SIV3D_ENGINE(Audio)->getBus(busIndex).getBus()
				.play(*m_audioSource,
					static_cast<float>(m_reservedSetting.volume),
					static_cast<float>(m_reservedSetting.pan), true);

			if (m_reservedSetting.pos.count() != 0.0)
			{
				m_pSoloud->seek(m_handle, m_reservedSetting.pos.count());
			}

			if (m_reservedSetting.speed != 1.0)
			{
				m_pSoloud->setRelativePlaySpeed(m_handle, static_cast<float>(m_reservedSetting.speed));
			}

			m_pSoloud->setPause(m_handle, false);

			m_reservedSetting = {};
		}
		else if (m_pSoloud->getPause(m_handle)) // Pause の終了
		{
			m_pSoloud->setPause(m_handle, false);
		}
	}

	void AudioData::play(const size_t busIndex, const Duration& duration)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle)) // 初回の再生
		{
			m_busIndex = static_cast<uint32>(busIndex);

			m_handle = SIV3D_ENGINE(Audio)->getBus(busIndex).getBus()
				.play(*m_audioSource,
					0.0f,
					static_cast<float>(m_reservedSetting.pan), true);
			
			if (m_reservedSetting.pos.count() != 0.0)
			{
				m_pSoloud->seek(m_handle, m_reservedSetting.pos.count());
			}
	
			if (m_reservedSetting.speed != 1.0)
			{
				m_pSoloud->setRelativePlaySpeed(m_handle, static_cast<float>(m_reservedSetting.speed));
			}
			
			m_pSoloud->fadeVolume(m_handle, 1.0f, duration.count());

			m_pSoloud->setPause(m_handle, false);

			m_reservedSetting = {};
		}
		else if (m_pSoloud->getPause(m_handle)) // Pause の終了
		{
			m_pSoloud->setVolume(m_handle, 0.0f);

			m_pSoloud->fadeVolume(m_handle, 1.0f, duration.count());
			
			m_pSoloud->setPause(m_handle, false);
		}
	}

	void AudioData::pause()
	{
		m_pSoloud->setPause(m_handle, true);
	}

	void AudioData::pause(const Duration& duration)
	{
		m_pSoloud->fadeVolume(m_handle, 0.0f, duration.count());
		m_pSoloud->schedulePause(m_handle, duration.count());
	}

	void AudioData::stop()
	{
		m_pSoloud->stop(m_handle);
		m_handle = 0;
	}

	void AudioData::stop(const Duration& duration)
	{
		m_pSoloud->fadeVolume(m_handle, 0.0f, duration.count());
		m_pSoloud->scheduleStop(m_handle, duration.count());
	}

	void AudioData::playOneShot(const size_t busIndex, const double volume, const double pan, const double speed)
	{
		clearInvalidShots();

		const SoLoud::handle shotHandle = SIV3D_ENGINE(Audio)->getBus(busIndex).getBus()
			.play(*m_audioSource,
				static_cast<float>(volume),
				static_cast<float>(pan), false);

		if (speed != 1.0)
		{
			m_pSoloud->setRelativePlaySpeed(shotHandle, static_cast<float>(speed));
		}

		m_pSoloud->setPause(shotHandle, false);

		m_shotHandles << shotHandle;
	}

	void AudioData::pauseAllShots()
	{
		clearInvalidShots();

		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->setPause(shotHandle, true);
		}
	}

	void AudioData::pauseAllShots(const Duration& fadeTime)
	{
		clearInvalidShots();

		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->fadeVolume(shotHandle, 0.0f, fadeTime.count());
			m_pSoloud->schedulePause(shotHandle, fadeTime.count());
		}
	}

	void AudioData::resumeAllShots()
	{
		clearInvalidShots();

		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->setPause(shotHandle, false);
		}
	}

	void AudioData::resumeAllShots(const Duration& fadeTime)
	{
		clearInvalidShots();

		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->setVolume(shotHandle, 0.0f);
			m_pSoloud->fadeVolume(shotHandle, 1.0f, fadeTime.count());
			m_pSoloud->setPause(shotHandle, false);
		}
	}

	void AudioData::stopAllShots()
	{
		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->stop(shotHandle);
		}

		m_shotHandles.clear();
	}

	void AudioData::stopAllShots(const Duration& fadeTime)
	{
		clearInvalidShots();

		for (const auto& shotHandle : m_shotHandles)
		{
			m_pSoloud->fadeVolume(shotHandle, 0.0f, fadeTime.count());
			m_pSoloud->scheduleStop(shotHandle, fadeTime.count());
		}
	}


	SoLoud::handle AudioData::makeHandle()
	{
		return m_pSoloud->play(*m_audioSource, -1.0f, 0.0f, true);
	}


	double AudioData::posSec() const
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			return m_reservedSetting.pos.count();
		}

		return m_pSoloud->getStreamPosition(m_handle);
	}

	void AudioData::seekTo(const Duration& pos)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			m_reservedSetting.pos = pos;
			return;
		}

		const bool isPlaying = (m_pSoloud->getPause(m_handle) == false);

		m_reservedSetting.volume	= m_pSoloud->getVolume(m_handle);
		m_reservedSetting.pan		= m_pSoloud->getPan(m_handle);
		m_reservedSetting.speed		= m_pSoloud->getRelativePlaySpeed(m_handle);
		m_reservedSetting.pos		= pos;

		m_pSoloud->stop(m_handle);
		m_handle = 0;

		{
			m_handle = SIV3D_ENGINE(Audio)->getBus(m_busIndex).getBus()
				.play(*m_audioSource,
					static_cast<float>(m_reservedSetting.volume),
					static_cast<float>(m_reservedSetting.pan), true);

			if (m_reservedSetting.pos.count() != 0.0)
			{
				m_pSoloud->seek(m_handle, m_reservedSetting.pos.count());
			}

			if (m_reservedSetting.speed != 1.0)
			{
				m_pSoloud->setRelativePlaySpeed(m_handle, static_cast<float>(m_reservedSetting.speed));
			}

			if (isPlaying)
			{
				m_pSoloud->setPause(m_handle, false);
			}

			m_reservedSetting = {};
		}
	}

	size_t AudioData::getLoopCount() const
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			return 0;
		}

		return m_pSoloud->getLoopCount(m_handle);
	}

	double AudioData::getVolume() const
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			return m_reservedSetting.volume;
		}

		return m_pSoloud->getVolume(m_handle);
	}

	void AudioData::setVolume(const double volume)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			m_reservedSetting.volume = volume;
			return;
		}

		m_pSoloud->setVolume(m_handle, static_cast<float>(volume));
	}

	void AudioData::fadeVolume(const double volume, const Duration& time)
	{
		m_pSoloud->fadeVolume(m_handle, static_cast<float>(volume), time.count());
	}

	double AudioData::getPan() const
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			return m_reservedSetting.pan;
		}

		return m_pSoloud->getPan(m_handle);
	}

	void AudioData::setPan(const double pan)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			m_reservedSetting.pan = pan;
			return;
		}

		m_pSoloud->setPan(m_handle, static_cast<float>(pan));
	}

	void AudioData::fadePan(const double pan, const Duration& time)
	{
		m_pSoloud->fadePan(m_handle, static_cast<float>(pan), time.count());
	}

	double AudioData::getSpeed() const
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			return m_reservedSetting.speed;
		}

		return m_pSoloud->getRelativePlaySpeed(m_handle);
	}

	void AudioData::setSpeed(const double speed)
	{
		if (not m_pSoloud->isValidVoiceHandle(m_handle))
		{
			m_reservedSetting.speed = speed;
			return;
		}

		m_pSoloud->setRelativePlaySpeed(m_handle, static_cast<float>(speed));
	}

	void AudioData::fadeSpeed(const double speed, const Duration& time)
	{
		m_pSoloud->fadeRelativePlaySpeed(m_handle, static_cast<float>(speed), time.count());
	}

	const float* AudioData::getSamples(const size_t channel) const
	{
		if (m_isStreaming)
		{
			return nullptr;
		}

		const float* pSrc = &m_wave[0].left;

		if (channel == 0)
		{
			return pSrc;
		}
		else
		{
			return (pSrc + m_lengthSample);
		}
	}

	void AudioData::clearInvalidShots()
	{
		m_shotHandles.remove_if([this](auto handle)
			{
				return (not m_pSoloud->isValidVoiceHandle(handle));
			});
	}
}
