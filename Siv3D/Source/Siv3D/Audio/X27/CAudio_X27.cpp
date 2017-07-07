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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN8
# define  NTDDI_VERSION NTDDI_WIN8
# include <Windows.h>
# include "CAudio_X27.hpp"
# include "../../EngineUtility.hpp"
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	std::atomic_bool CAudio_X27::fadeManagementEnabled{ true };

	namespace detail
	{
		ISiv3DAudio* CreateCAudio_X27()
		{
			return new CAudio_X27;
		}

		static void FadingManagement(int)
		{
			for (;;)
			{
				if (!Siv3DEngine::GetAudio()->updateFade())
				{
					break;
				}

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

		m_hasAudioDevice = true;
	}

	CAudio_X27::~CAudio_X27()
	{
		fadeManagementEnabled = false;

		if (m_fadeManagingThread.joinable())
		{
			m_fadeManagingThread.join();
		}

		m_audios.destroy();

		m_device.release();
	}

	bool CAudio_X27::hasAudioDevice() const
	{
		return m_hasAudioDevice;
	}

	bool CAudio_X27::init()
	{
		if (FAILED(m_device.xAudio2->GetDeviceDetails(0, &m_device.deviceDetails)))
		{
			//LOG_FAIL(L"XAudio2: オーディオデバイス情報の取得に失敗しました。");
			return false;
		}
		else
		{
			//LOG_INFO(L"サウンドデバイス: ", m_audio.deviceDetails.DisplayName);
		}

		const auto nullAudio = std::make_shared<Audio_X27>(
			Wave(SecondsF(0.5), Arg::generator = [](double t) {
				return 0.5 * std::sin(t * Math::TwoPi) * std::sin(t * Math::TwoPi * 220.0 * (t * 4.0 + 1.0)); }),
			&m_device,
			none,
			1.0);

		if (!nullAudio->isInitialized())
		{
			return false;
		}

		m_audios.setNullData(nullAudio);

		m_fadeManagingThread = std::thread(detail::FadingManagement, 0);

		return true;
	}

	Audio::IDType CAudio_X27::create(Wave&& wave)
	{
		if (!wave)
		{
			return Audio::NullHandleID;
		}

		const auto audio = std::make_shared<Audio_X27>(
			std::move(wave),
			&m_device,
			none,
			1.0);

		if (!audio->isInitialized())
		{
			return Audio::NullHandleID;
		}

		return m_audios.add(audio);
	}

	void CAudio_X27::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}

	uint32 CAudio_X27::samplingRate(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samplingRate();
	}

	size_t CAudio_X27::samples(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samples();
	}

	void CAudio_X27::setLoop(const Audio::IDType handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setLoop(loop, loopBeginSample, loopEndSample);
	}

	bool CAudio_X27::play(const Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeinDuration.count()), 0.0);

		return m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PlayWithFade : AudioControlState::PlayImmediately,
			fadeSec);
	}

	void CAudio_X27::pause(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PauseWithFade : AudioControlState::PauseImmediately,
			fadeSec);
	}

	void CAudio_X27::stop(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::StopWithFade : AudioControlState::StopImmediately,
			fadeSec);
	}

	uint64 CAudio_X27::posSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->posSample();
	}

	uint64 CAudio_X27::streamPosSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->streamPosSample();
	}
	
	uint64 CAudio_X27::samplesPlayed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->samplesPlayed();
	}

	void CAudio_X27::setVolume(const Audio::IDType handleID, const std::pair<double, double>& volume)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setVolume(volume);
	}

	std::pair<double, double> CAudio_X27::getVolume(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getVolume();
	}

	void CAudio_X27::setSpeed(const Audio::IDType handleID, const double speed)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setSpeed(speed);
	}

	double CAudio_X27::getSpeed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getSpeed();
	}

	std::pair<double, double> CAudio_X27::getMinMaxSpeed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getMinMaxSpeed();
	}

	bool CAudio_X27::updateFade()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		for (const auto& audio : m_audios)
		{
			audio.second->updateFadeManager();
		}

		return fadeManagementEnabled;
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

# endif
