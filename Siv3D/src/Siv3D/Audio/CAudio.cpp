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

		if (m_soloud)
		{
			// 再生中の音声をフェードアウト
			if (m_soloud->getActiveVoiceCount())
			{
				constexpr SecondsF FadeOutTime{ 0.3 };

				m_soloud->fadeGlobalVolume(0.0f, FadeOutTime.count());
				
				System::Sleep(FadeOutTime);
			}
		}

		for (auto& bus : m_buses)
		{
			bus.reset();
		}

		m_audios.destroy();

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
			auto nullAudio = std::make_unique<AudioData>(AudioData::Null{});

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
		auto audio = std::make_unique<AudioData>(std::move(wave), loop);

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
		auto audio = std::make_unique<AudioData>(path);

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
		auto audio = std::make_unique<AudioData>(path, loopBegin);

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
}
