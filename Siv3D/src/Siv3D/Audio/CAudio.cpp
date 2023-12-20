//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/FFTResult.hpp>
# include <Siv3D/FFTSampleLength.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/KlattTTSParameters.hpp>
# include <Siv3D/DLL.hpp>
# include "CAudio.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static String ToInfo(const std::unique_ptr<AudioData>& audio)
		{
			const uint32 sampleRate = audio->sampleRate();
			const uint32 samples = audio->samples();

			return U"(sampleRate: {0}Hz, samples: {1} ({2:.1f}s), loopTiming: {3}, {4}, isStreaming: {5})"_fmt(
				sampleRate, samples,
				(static_cast<double>(samples) / sampleRate),
				audio->loopTiming().beginPos, audio->loopTiming().endPos, audio->isStreaming());
		}
	}

	CAudio::CAudio() {}

	CAudio::~CAudio()
	{
		LOG_SCOPED_TRACE(U"CAudio::~CAudio()");

		m_speech.reset();

		m_audios.destroy();

		for (auto& bus : m_buses)
		{
			bus.reset();
		}

		if (m_soloud)
		{
			LOG_TRACE(U"m_soloud->deinit()");
			m_soloud->deinit();

			LOG_TRACE(U"m_soloud.reset()");
			m_soloud.reset();
		}

	# if SIV3D_PLATFORM(WINDOWS) || SIV3D_PLATFORM(MACOS)

		DLL::Unload(m_soundTouch);

	# else


	# endif
	}

	void CAudio::init()
	{
		LOG_SCOPED_TRACE(U"CAudio::init()");

		// Soloud の初期化
		{
			m_soloud = std::make_unique<SoLoud::Soloud>();

		# if SIV3D_PLATFORM(WEB)
			if (SoLoud::SO_NO_ERROR != m_soloud->init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::AUTO, SoLoud::Soloud::AUTO, 4096))
			{
				throw EngineError{ U"Failed to initialize audio engine" };
			}
		# else
			if (SoLoud::SO_NO_ERROR != m_soloud->init())
			{
				throw EngineError{ U"Failed to initialize audio engine" };
			}
		# endif

			LOG_INFO(U"🎧 Audio backend: {0} (channel count: {1}, sample rate: {2}, buffer size: {3})"_fmt(
				Unicode::Widen(m_soloud->getBackendString()),
				m_soloud->getBackendChannels(),
				m_soloud->getBackendSamplerate(),
				m_soloud->getBackendBufferSize()));

			m_soloud->setVisualizationEnable(true);
			m_soloud->setMaxActiveVoiceCount(MaxActiveVoiceCount);
		}

		// null Audio を管理に登録
		{
			// null Font を作成
			auto nullAudio = std::make_unique<AudioData>(AudioData::Null{}, m_soloud.get());

			if (not nullAudio->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null Audio initialization failed" };
			}

			// 管理に登録
			m_audios.setNullData(std::move(nullAudio));
		}

	# if SIV3D_PLATFORM(WINDOWS)

		m_soundTouch = DLL::Load(U"dll/soundtouch/SoundTouch_x64.dll");

		if (m_soundTouch)
		{
			m_soundTouchAvailable = true;

			try
			{
				m_soundTouchFunctions.p_soundtouch_createInstance = DLL::GetFunction(m_soundTouch, "soundtouch_createInstance");
				m_soundTouchFunctions.p_soundtouch_destroyInstance = DLL::GetFunction(m_soundTouch, "soundtouch_destroyInstance");
				m_soundTouchFunctions.p_soundtouch_setPitchSemiTones = DLL::GetFunction(m_soundTouch, "soundtouch_setPitchSemiTones");
				m_soundTouchFunctions.p_soundtouch_setChannels = DLL::GetFunction(m_soundTouch, "soundtouch_setChannels");
				m_soundTouchFunctions.p_soundtouch_setSampleRate = DLL::GetFunction(m_soundTouch, "soundtouch_setSampleRate");
				m_soundTouchFunctions.p_soundtouch_putSamples = DLL::GetFunction(m_soundTouch, "soundtouch_putSamples");
				m_soundTouchFunctions.p_soundtouch_receiveSamples = DLL::GetFunction(m_soundTouch, "soundtouch_receiveSamples");
				m_soundTouchFunctions.p_soundtouch_numSamples = DLL::GetFunction(m_soundTouch, "soundtouch_numSamples");
			}
			catch (const EngineError&)
			{
				m_soundTouchAvailable = false;
			}
		}

	# elif SIV3D_PLATFORM(MACOS)
		
		m_soundTouch = DLL::Load(Resource(U"engine/lib/soundtouch/libSoundTouch.dylib"));

		if (m_soundTouch)
		{
			m_soundTouchAvailable = true;

			try
			{
				m_soundTouchFunctions.p_soundtouch_createInstance = DLL::GetFunction(m_soundTouch, "soundtouch_createInstance");
				m_soundTouchFunctions.p_soundtouch_destroyInstance = DLL::GetFunction(m_soundTouch, "soundtouch_destroyInstance");
				m_soundTouchFunctions.p_soundtouch_setPitchSemiTones = DLL::GetFunction(m_soundTouch, "soundtouch_setPitchSemiTones");
				m_soundTouchFunctions.p_soundtouch_setChannels = DLL::GetFunction(m_soundTouch, "soundtouch_setChannels");
				m_soundTouchFunctions.p_soundtouch_setSampleRate = DLL::GetFunction(m_soundTouch, "soundtouch_setSampleRate");
				m_soundTouchFunctions.p_soundtouch_putSamples = DLL::GetFunction(m_soundTouch, "soundtouch_putSamples");
				m_soundTouchFunctions.p_soundtouch_receiveSamples = DLL::GetFunction(m_soundTouch, "soundtouch_receiveSamples");
				m_soundTouchFunctions.p_soundtouch_numSamples = DLL::GetFunction(m_soundTouch, "soundtouch_numSamples");
			}
			catch (const EngineError&)
			{
				m_soundTouchAvailable = false;
			}
		}
		
	# elif SIV3D_PLATFORM(LINUX)

		m_soundTouch = DLL::Load(U"libSoundTouch.so");

		if (m_soundTouch)
		{
			m_soundTouchAvailable = true;

			try
			{
				m_soundTouchFunctions.p_soundtouch_createInstance = soundtouch_createInstance;
				m_soundTouchFunctions.p_soundtouch_destroyInstance = soundtouch_destroyInstance;
				m_soundTouchFunctions.p_soundtouch_setPitchSemiTones = soundtouch_setPitchSemiTones;
				m_soundTouchFunctions.p_soundtouch_setChannels = soundtouch_setChannels;
				m_soundTouchFunctions.p_soundtouch_setSampleRate = soundtouch_setSampleRate;
				m_soundTouchFunctions.p_soundtouch_putSamples = soundtouch_putSamples;
				m_soundTouchFunctions.p_soundtouch_receiveSamples = soundtouch_receiveSamples;
				m_soundTouchFunctions.p_soundtouch_numSamples = soundtouch_numSamples;
			}
			catch (const EngineError&)
			{
				m_soundTouchAvailable = false;
			}
		}

	# endif

		if (m_soundTouchAvailable)
		{
			LOG_INFO(U"ℹ️ SoundTouch is available");
		}
	}

	size_t CAudio::getAudioCount() const
	{
		return m_audios.size();
	}

	Audio::IDType CAudio::create(Wave&& wave, const Optional<AudioLoopTiming>& loop)
	{
		if (not wave)
		{
			return Audio::IDType::NullAsset();
		}

		// Audio を作成
		auto audio = std::make_unique<AudioData>(m_soloud.get(), std::move(wave), loop);

		if (not audio->isInitialized()) // もし作成に失敗していたら
		{
			return Audio::IDType::NullAsset();
		}

		const String info = detail::ToInfo(audio);

		// Audio を管理に登録
		return m_audios.add(std::move(audio), info);
	}

	Audio::IDType CAudio::create(Wave&& wave, const Duration& loopBegin, const Duration& loopEnd)
	{
		const uint64 loopBeginSample = static_cast<uint64>(loopBegin.count() * wave.sampleRate());
		const uint64 loopEndSample = static_cast<uint64>(loopEnd.count() * wave.sampleRate());
		return create(std::move(wave), AudioLoopTiming{ loopBeginSample, loopEndSample });
	}

	Audio::IDType CAudio::createStreamingNonLoop(const FilePathView path)
	{
		// ストリーミングに対応しない形式の場合のフォールバック
		if (const AudioFormat format = AudioDecoder::GetAudioFormat(path);
			(format != AudioFormat::WAVE)
			&& (format != AudioFormat::MP3)
			&& (format != AudioFormat::OggVorbis)
			&& (format != AudioFormat::FLAC))
		{
			return create(Wave{ path }, none);
		}

		// Audio を作成
		auto audio = std::make_unique<AudioData>(m_soloud.get(), path);

		if (not audio->isInitialized()) // もし作成に失敗していたら
		{
			return Audio::IDType::NullAsset();
		}

		const String info = detail::ToInfo(audio);

		// Audio を管理に登録
		return m_audios.add(std::move(audio), info);
	}

	Audio::IDType CAudio::createStreamingLoop(const FilePathView path, const uint64 loopBegin)
	{
		// ストリーミングに対応しない形式の場合のフォールバック
		if (const AudioFormat format = AudioDecoder::GetAudioFormat(path);
			(format != AudioFormat::WAVE)
			&& (format != AudioFormat::MP3)
			&& (format != AudioFormat::OggVorbis)
			&& (format != AudioFormat::FLAC))
		{
			return create(Wave{ path }, AudioLoopTiming{ loopBegin, 0 });
		}

		// Audio を作成
		auto audio = std::make_unique<AudioData>(m_soloud.get(), path, loopBegin);

		if (not audio->isInitialized()) // もし作成に失敗していたら
		{
			return Audio::IDType::NullAsset();
		}

		const String info = detail::ToInfo(audio);

		// Audio を管理に登録
		return m_audios.add(std::move(audio), info);
	}

	Audio::IDType CAudio::createDynamic(const std::shared_ptr<IAudioStream>& pAudioStream, const Arg::sampleRate_<uint32> sampleRate)
	{
		// Audio を作成
		auto audio = std::make_unique<AudioData>(AudioData::Dynamic{}, m_soloud.get(), pAudioStream, sampleRate);

		if (not audio->isInitialized()) // もし作成に失敗していたら
		{
			return Audio::IDType::NullAsset();
		}

		const String info = detail::ToInfo(audio);

		// Audio を管理に登録
		return m_audios.add(std::move(audio), info);
	}

	void CAudio::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}

	bool CAudio::isStreaming(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isStreaming();
	}

	uint32 CAudio::sampleRate(const Audio::IDType handleID)
	{
		return m_audios[handleID]->sampleRate();
	}

	size_t CAudio::samples(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samples();
	}

	int64 CAudio::samplesPlayed(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samplesPlayed();
	}

	bool CAudio::isActive(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isActive();
	}

	bool CAudio::isPlaying(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isPlaying();
	}

	bool CAudio::isPaused(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isPaused();
	}

	bool CAudio::isLoop(const Audio::IDType handleID)
	{
		return m_audios[handleID]->isLoop();
	}

	AudioLoopTiming CAudio::getLoopTiming(const Audio::IDType handleID)
	{
		return m_audios[handleID]->loopTiming();
	}

	void CAudio::setLoop(const Audio::IDType handleID, const bool loop)
	{
		m_audios[handleID]->setLoop(loop);
	}

	void CAudio::setLoopPoint(const Audio::IDType handleID, const Duration& loopBegin)
	{
		m_audios[handleID]->setLoopPoint(loopBegin);
	}

	void CAudio::play(const Audio::IDType handleID, const size_t busIndex)
	{
		m_audios[handleID]->play(busIndex);
	}

	void CAudio::play(const Audio::IDType handleID, const size_t busIndex, const Duration& duration)
	{
		m_audios[handleID]->play(busIndex, duration);
	}

	void CAudio::pause(const Audio::IDType handleID)
	{
		m_audios[handleID]->pause();
	}

	void CAudio::pause(const Audio::IDType handleID, const Duration& duration)
	{
		m_audios[handleID]->pause(duration);
	}

	void CAudio::stop(const Audio::IDType handleID)
	{
		m_audios[handleID]->stop();
	}

	void CAudio::stop(const Audio::IDType handleID, const Duration& duration)
	{
		m_audios[handleID]->stop(duration);
	}

	void CAudio::playOneShot(const Audio::IDType handleID, const size_t busIndex, const double volume, const double pan, const double speed)
	{
		m_audios[handleID]->playOneShot(busIndex, volume, pan, speed);
	}

	void CAudio::pauseAllShots(const Audio::IDType handleID)
	{
		m_audios[handleID]->pauseAllShots();
	}

	void CAudio::pauseAllShots(Audio::IDType handleID, const Duration& fadeTime)
	{
		m_audios[handleID]->pauseAllShots(fadeTime);
	}

	void CAudio::resumeAllShots(const Audio::IDType handleID)
	{
		m_audios[handleID]->resumeAllShots();
	}

	void CAudio::resumeAllShots(Audio::IDType handleID, const Duration& fadeTime)
	{
		m_audios[handleID]->resumeAllShots(fadeTime);
	}

	void CAudio::stopAllShots(const Audio::IDType handleID)
	{
		m_audios[handleID]->stopAllShots();
	}

	void CAudio::stopAllShots(Audio::IDType handleID, const Duration& fadeTime)
	{
		m_audios[handleID]->stopAllShots(fadeTime);
	}


	uint32 CAudio::createAudioGroup(const Array<Audio::IDType>& handleIDs, Array<uint32>& handles)
	{
		handles.clear();

		SoLoud::handle groupHandle = m_soloud->createVoiceGroup();

		for (const auto& handleID : handleIDs)
		{
			const SoLoud::handle handle = m_audios[handleID]->makeHandle();

			m_soloud->addVoiceToGroup(groupHandle, handle);
			
			handles << handle;
		}

		return groupHandle;
	}



	double CAudio::posSec(const Audio::IDType handleID)
	{
		return m_audios[handleID]->posSec();
	}

	void CAudio::seekTo(const Audio::IDType handleID, const Duration& pos)
	{
		m_audios[handleID]->seekTo(pos);
	}

	size_t CAudio::getLoopCount(const Audio::IDType handleID)
	{
		return m_audios[handleID]->getLoopCount();
	}

	double CAudio::getVolume(const Audio::IDType handleID)
	{
		return m_audios[handleID]->getVolume();
	}

	void CAudio::setVolume(const Audio::IDType handleID, const double volume)
	{
		m_audios[handleID]->setVolume(volume);
	}

	void CAudio::fadeVolume(const Audio::IDType handleID, const double volume, const Duration& time)
	{
		m_audios[handleID]->fadeVolume(volume, time);
	}

	double CAudio::getPan(const Audio::IDType handleID)
	{
		return m_audios[handleID]->getPan();
	}

	void CAudio::setPan(const Audio::IDType handleID, const double pan)
	{
		m_audios[handleID]->setPan(pan);
	}

	void CAudio::fadePan(const Audio::IDType handleID, const double pan, const Duration& time)
	{
		m_audios[handleID]->fadePan(pan, time);
	}

	double CAudio::getSpeed(const Audio::IDType handleID)
	{
		return m_audios[handleID]->getSpeed();
	}

	void CAudio::setSpeed(const Audio::IDType handleID, const double speed)
	{
		m_audios[handleID]->setSpeed(speed);
	}

	void CAudio::fadeSpeed(const Audio::IDType handleID, const double speed, const Duration& time)
	{
		m_audios[handleID]->fadeSpeed(speed, time);
	}

	const float* CAudio::getSamples(const Audio::IDType handleID, const size_t channel)
	{
		return m_audios[handleID]->getSamples(channel);
	}


	size_t CAudio::getActiveVoiceCount()
	{
		return m_soloud->getActiveVoiceCount();
	}

	void CAudio::globalPause()
	{
		m_soloud->setPauseAll(true);
	}

	void CAudio::globalResume()
	{
		m_soloud->setPauseAll(false);
	}

	double CAudio::getGlobalVolume()
	{
		return m_soloud->getGlobalVolume();
	}

	void CAudio::setGlobalVolume(double volume)
	{
		m_soloud->setGlobalVolume(static_cast<float>(volume));
	}

	void CAudio::fadeGlobalVolume(const double volume, const Duration& time)
	{
		m_soloud->fadeGlobalVolume(static_cast<float>(volume), time.count());
	}

	void CAudio::getGlobalSamples(Array<float>& samples)
	{
		if (const float* p = m_soloud->getWave())
		{
			samples.assign(p, p + 256);
		}
		else
		{
			samples.clear();
		}
	}

	void CAudio::getGlobalFFT(FFTResult& result)
	{
		result.buffer.clear();
		result.resolution = 0.0;
		result.sampleRate = 0;

		if (const float* p = m_soloud->calcFFT())
		{
			const uint32 sampleRate = m_soloud->mSamplerate;
			result.buffer.assign(p, p + 256);
			result.resolution = static_cast<double>(sampleRate) / (256 << static_cast<int32>(FFTSampleLength::SL512));
			result.sampleRate = sampleRate;

			for (auto& x : result.buffer)
			{
				x *= 0.25f;
			}
		}
	}

	void CAudio::getBusSamples(const size_t busIndex, Array<float>& samples)
	{
		samples.clear();

		if (Audio::MaxBusCount <= busIndex)
		{
			return;
		}
		
		if (not m_buses[busIndex])
		{
			return;
		}

		if (const float* p = m_buses[busIndex]->getBus().getWave())
		{
			samples.assign(p, p + 256);
		}
	}

	void CAudio::getBusFFT(const size_t busIndex, FFTResult& result)
	{
		result.buffer.clear();
		result.resolution = 0.0;
		result.sampleRate = 0;

		if (Audio::MaxBusCount <= busIndex)
		{
			return;
		}

		if (not m_buses[busIndex])
		{
			return;
		}

		if (const float* p = m_buses[busIndex]->getBus().calcFFT())
		{
			const uint32 sampleRate = static_cast<uint32>(m_buses[busIndex]->getBus().mBaseSamplerate);
			result.buffer.assign(p, p + 256);
			result.resolution = static_cast<double>(sampleRate) / (256 << static_cast<int32>(FFTSampleLength::SL512));
			result.sampleRate = sampleRate;

			for (auto& x : result.buffer)
			{
				x *= 0.25f;
			}
		}
	}

	double CAudio::getBusVolume(const size_t busIndex)
	{
		if (not m_buses[busIndex])
		{
			return 0.0;
		}

		return m_buses[busIndex]->getVolume();
	}

	void CAudio::setBusVolume(const size_t busIndex, const double volume)
	{
		getBus(busIndex).setVolume(volume);
	}

	void CAudio::fadeBusVolume(const size_t busIndex, const double volume, const Duration& time)
	{
		getBus(busIndex).fadeVolume(volume, time);
	}

	void CAudio::clearFilter(const size_t busIndex, const size_t filterIndex)
	{
		if (not m_buses[busIndex])
		{
			return;
		}

		getBus(busIndex).clearFilter(filterIndex);
	}

	void CAudio::setLowPassFilter(const size_t busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
	{
		getBus(busIndex).setLowPassFilter(filterIndex, cutoffFrequency, resonance, wet);
	}

	void CAudio::setHighPassFilter(const size_t busIndex, const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
	{
		getBus(busIndex).setHighPassFilter(filterIndex, cutoffFrequency, resonance, wet);
	}

	void CAudio::setEchoFilter(const size_t busIndex, const size_t filterIndex, const double delay, const double decay, const double wet)
	{
		getBus(busIndex).setEchoFilter(filterIndex, delay, decay, wet);
	}

	void CAudio::setReverbFilter(const size_t busIndex, const size_t filterIndex, const bool freeze, const double roomSize, const double damp, const double width, const double wet)
	{
		getBus(busIndex).setReverbFilter(filterIndex, freeze, roomSize, damp, width, wet);
	}

	void CAudio::setPitchShiftFilter(const size_t busIndex, const size_t filterIndex, const double pitchShift)
	{
		getBus(busIndex).setPitchShiftFilter(filterIndex, pitchShift);
	}

	AudioBus& CAudio::getBus(const size_t busIndex)
	{
		assert(busIndex < Audio::MaxBusCount);

		if (not m_buses[busIndex])
		{
			m_buses[busIndex] = std::make_unique<AudioBus>(m_soloud.get());
		}

		return *m_buses[busIndex];
	}

	SoLoud::Soloud& CAudio::getSoloud()
	{
		return *m_soloud;
	}

	const SoundTouchFunctions* CAudio::getSoundTouchFunctions() const noexcept
	{
		if (not m_soundTouchAvailable)
		{
			return nullptr;
		}

		return &m_soundTouchFunctions;
	}

	bool CAudio::supportsPitchShift() const noexcept
	{
		return m_soundTouchAvailable;
	}


	void CAudio::speakKlatt(const StringView text, const KlattTTSParameters& param)
	{
		m_speech = std::make_unique<AudioData>(AudioData::TextToSpeech{}, m_soloud.get(), text, param);
		
		m_speech->play(0);
		
		m_speech->setSpeed(param.speed);
	}
	
	bool CAudio::isSpeakingKlatt()
	{
		if (not m_speech)
		{
			return false;
		}

		return m_speech->isPlaying();
	}
	
	void CAudio::pauseKlatt()
	{
		if (not m_speech)
		{
			return;
		}

		m_speech->pause();
	}
	
	void CAudio::resumeKlatt()
	{
		if (not m_speech)
		{
			return;
		}

		m_speech->play(0);
	}
	
	void CAudio::stopKlatt()
	{
		if (not m_speech)
		{
			return;
		}

		m_speech->stop();
	}
}
