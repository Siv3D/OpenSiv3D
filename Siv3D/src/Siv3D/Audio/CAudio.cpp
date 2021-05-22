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
		// [Siv3D ToDo]
		return(Audio::IDType::NullAsset());
	}

	Audio::IDType CAudio::create(Wave&& wave, const Duration& loopBegin, const Duration& loopEnd)
	{
		// [Siv3D ToDo]
		return(Audio::IDType::NullAsset());
	}

	Audio::IDType CAudio::createStreamingNonLoop(FilePathView path)
	{
		// [Siv3D ToDo]
		return(Audio::IDType::NullAsset());
	}

	Audio::IDType CAudio::createStreamingLoop(FilePathView path, uint64 loopBegin)
	{
		// [Siv3D ToDo]
		return(Audio::IDType::NullAsset());
	}

	void CAudio::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}
}
