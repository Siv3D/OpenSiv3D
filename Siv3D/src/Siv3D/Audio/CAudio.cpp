//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/System.hpp>
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

		//if (m_soloud)
		//{
		//	// 再生中の音声をフェードアウト
		//	if (m_soloud->getActiveVoiceCount())
		//	{
		//		constexpr SecondsF FadeOutTime{ 0.3 };

		//		m_soloud->fadeGlobalVolume(0.0f, FadeOutTime.count());
		//		
		//		System::Sleep(FadeOutTime);
		//	}
		//}

		m_audios.destroy();

		for (auto& bus : m_buses)
		{
			bus.reset();
		}

		if (m_soloud)
		{
			LOG_TRACE(U"m_soloud->stopAll()");
			m_soloud->stopAll();

			LOG_TRACE(U"m_soloud->deinit()");
			m_soloud->deinit();

			LOG_TRACE(U"m_soloud.reset()");
			m_soloud.reset();
		}
	}

	void CAudio::init()
	{
		LOG_SCOPED_TRACE(U"CAudio::init()");

		// Soloud の初期化
		{
			m_soloud = std::make_unique<SoLoud::Soloud>();

			if (SoLoud::SO_NO_ERROR != m_soloud->init())
			{
				throw EngineError{ U"Failed to initialize audio engine" };
			}

			LOG_INFO(U"🎧 Audio backend: {0} (channel count: {1}, sample rate: {2}, buffer size: {3})"_fmt(
				Unicode::Widen(m_soloud->getBackendString()),
				m_soloud->getBackendChannels(),
				m_soloud->getBackendSamplerate(),
				m_soloud->getBackendBufferSize()));

			m_soloud->setVisualizationEnable(true);
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
	}

	Audio::IDType CAudio::create(Wave&& wave, const Optional<AudioLoopTiming>& loop)
	{
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



	double CAudio::posSec(const Audio::IDType handleID)
	{
		return m_audios[handleID]->posSec();
	}

	void CAudio::seekTo(const Audio::IDType handleID, const Duration& pos)
	{
		m_audios[handleID]->seekTo(pos);
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



	SoLoud::Bus& CAudio::getBus(const size_t busIndex)
	{
		assert(busIndex < Audio::MaxBusCount);

		if (not m_buses[busIndex])
		{
			m_buses[busIndex] = std::make_unique<AudioBus>(*m_soloud);
		}

		return m_buses[busIndex]->getBus();
	}
}
