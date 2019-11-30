//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Windows.hpp>
# include <Siv3DEngine.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CAudio_X27.hpp"

namespace s3d
{
	namespace detail
	{
		ISiv3DAudio* CreateCAudio_X27()
		{
			return new CAudio_X27;
		}

		static void FadingController()
		{
			while (Siv3DEngine::Get<ISiv3DAudio>()->updateFade())
			{
				::Sleep(20);
			}
		}
	}

	CAudio_X27::CAudio_X27()
	{
		if (FAILED(::XAudio2Create(&m_device.xAudio2, 0)))
		{
			//LOG_FAIL(L"XAudio2 の初期化に失敗しました。最新の DirectX ランタイムをインストールすることで解決する場合があります。");

			//::MessageBoxW(nullptr, L"XAudio2 の初期化に失敗しました。最新の DirectX ランタイムをインストールすることで解決する場合があります。", L"初期化エラー", MB_OK);

			//Internet::LaunchWebBrowser(L"https://www.microsoft.com/en-us/download/details.aspx?displaylang=en&id=35");

			return;
		}

		if (FAILED(m_device.xAudio2->CreateMasteringVoice(&m_device.masteringVoice)))
		{
			//LOG_FAIL(L"XAudio2: マスターボイスの作成に失敗しました。サウンドデバイスが有効か確認してください。");
			
			return;
		}
	}

	CAudio_X27::~CAudio_X27()
	{
		//LOG_TRACE(U"CAudio_X27::~CAudio_X27()");

		fadeControlEnabled = false;

		if (m_fadeControllerThread.joinable())
		{
			m_fadeControllerThread.join();
		}

		m_audios.destroy();

		m_device.release();
	}

	bool CAudio_X27::hasAudioDevice() const
	{
		return (m_device.masteringVoice != nullptr);
	}

	bool CAudio_X27::init()
	{
		LOG_TRACE(U"CAudio_X27::init()");

		if (FAILED(m_device.xAudio2->GetDeviceDetails(0, &m_device.deviceDetails)))
		{
			//LOG_FAIL(L"XAudio2: オーディオデバイス情報の取得に失敗しました。");
			return false;
		}
		else
		{
			//LOG_INFO(L"サウンドデバイス: ", m_audio.deviceDetails.DisplayName);
		}

		auto nullAudio = std::make_unique<Audio_X27>(
			Wave(SecondsF(0.5), Arg::generator = [](double t) {
				return 0.5 * std::sin(t * Math::Constants::TwoPi) * std::sin(t * Math::Constants::TwoPi * 220.0 * (t * 4.0 + 1.0)); }),
			&m_device,
			none,
			2.0);

		if (!nullAudio->isInitialized())
		{
			return false;
		}

		m_audios.setNullData(std::move(nullAudio));

		m_fadeControllerThread = std::thread(detail::FadingController);

		LOG_INFO(U"ℹ️ CAudio_X27 initialized");

		return true;
	}

	AudioID CAudio_X27::create(Wave&& wave)
	{
		if (!wave)
		{
			return AudioID::NullAsset();
		}

		auto audio = std::make_unique<Audio_X27>(
			std::move(wave),
			&m_device,
			none,
			2.0);

		if (!audio->isInitialized())
		{
			return AudioID::NullAsset();
		}

		return m_audios.add(std::move(audio));
	}

	void CAudio_X27::release(const AudioID handleID)
	{
		m_audios.erase(handleID);
	}

	uint32 CAudio_X27::samplingRate(const AudioID handleID)
	{
		return m_audios[handleID]->getWave().samplingRate();
	}

	size_t CAudio_X27::samples(const AudioID handleID)
	{
		return m_audios[handleID]->getWave().size();
	}

	void CAudio_X27::setLoop(const AudioID handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		std::lock_guard lock(m_mutex);

		m_audios[handleID]->getStream().setLoop(loop, loopBeginSample, loopEndSample);
	}

	Optional<AudioLoopTiming> CAudio_X27::getLoop(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().getLoop();
	}

	bool CAudio_X27::play(const AudioID handleID, const SecondsF& fadeinDuration)
	{
		std::lock_guard lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeinDuration.count()), 0.0);

		return m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PlayWithFade : AudioControlState::PlayImmediately,
			fadeSec);
	}

	void CAudio_X27::pause(const AudioID handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PauseWithFade : AudioControlState::PauseImmediately,
			fadeSec);
	}

	void CAudio_X27::stop(const AudioID handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::StopWithFade : AudioControlState::StopImmediately,
			fadeSec);
	}

	void CAudio_X27::playOneShot(const AudioID handleID, const double volume, const double pitch)
	{
		std::lock_guard lock(m_mutex);

		m_audios[handleID]->playOneShot(volume, pitch);
	}

	void CAudio_X27::stopAllShots(AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		m_audios[handleID]->stopAllShots();
	}

	bool CAudio_X27::isPlaying(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().isPlaying();
	}

	bool CAudio_X27::isPaused(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().isPaused();
	}

	uint64 CAudio_X27::posSample(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().calculatePosSample();
	}

	uint64 CAudio_X27::streamPosSample(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().streamPosSample();
	}
	
	uint64 CAudio_X27::samplesPlayed(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().getSamplesPlayed();
	}

	const Wave& CAudio_X27::getWave(const AudioID handleID)
	{
		return m_audios[handleID]->getWave();
	}

	void CAudio_X27::setPosSample(const AudioID handleID, const int64 sample)
	{
		std::lock_guard lock(m_mutex);

		const auto& audio = m_audios[handleID];
		const auto currentState = audio->getState();
		const bool isPlaying = audio->getStream().isPlaying();

		audio->changeState(AudioControlState::StopImmediately, 0.0);
		audio->setPosSample(sample);

		if (isPlaying)
		{
			audio->changeState(currentState, 0.0);
		}
		else
		{
			audio->changeState(AudioControlState::StopImmediately, 0.0);
		}
	}

	void CAudio_X27::setVolume(const AudioID handleID, const std::pair<double, double>& volume)
	{
		std::lock_guard lock(m_mutex);

		m_audios[handleID]->getStream().setVolume(volume);
	}

	std::pair<double, double> CAudio_X27::getVolume(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().getVolume();
	}

	void CAudio_X27::setSpeed(const AudioID handleID, const double speed)
	{
		std::lock_guard lock(m_mutex);

		m_audios[handleID]->getStream().setSpeed(speed);
	}

	double CAudio_X27::getSpeed(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().getSpeed();
	}

	std::pair<double, double> CAudio_X27::getMinMaxSpeed(const AudioID handleID)
	{
		std::lock_guard lock(m_mutex);

		return m_audios[handleID]->getStream().getMinMaxSpeed();
	}

	bool CAudio_X27::updateFade()
	{
		std::lock_guard lock(m_mutex);

		for (const auto& audio : m_audios)
		{
			audio.second->updateFade();
		}

		return fadeControlEnabled;
	}

	void CAudio_X27::fadeMasterVolume()
	{
		while (m_masterVolume > 0.0005)
		{
			m_masterVolume *= 0.75;

			m_device.masteringVoice->SetVolume(static_cast<float>(m_masterVolume));

			::Sleep(10);
		}
	}
}
