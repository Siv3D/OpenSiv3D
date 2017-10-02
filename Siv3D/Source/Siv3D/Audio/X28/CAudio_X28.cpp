﻿//-----------------------------------------------
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
# include "CAudio_X28.hpp"
# include "../../EngineUtility.hpp"
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	std::atomic_bool CAudio_X28::fadeManagementEnabled{ true };

	namespace detail
	{
		bool CAudio_X28_IsAvailable()
		{
			if (HINSTANCE xaudio28 = ::LoadLibraryW(L"xaudio2_8.dll"))
			{
				::FreeLibrary(xaudio28);

				return true;
			}

			return false;
		}

		ISiv3DAudio* CreateCAudio_X28()
		{
			return new CAudio_X28;
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

	CAudio_X28::CAudio_X28()
	{
		m_xaudio28 = ::LoadLibraryW(L"xaudio2_8.dll");

		if (!m_xaudio28)
		{
			return;
		}

		p_XAudio2Create = FunctionPointer(m_xaudio28, "XAudio2Create");

		if (!p_XAudio2Create)
		{
			return;
		}

		if (FAILED(p_XAudio2Create(&m_device.xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
			return;
		}

		if (FAILED(m_device.xAudio2->CreateMasteringVoice(&m_device.masteringVoice)))
		{
			return;
		}

		m_hasAudioDevice = true;
	}

	CAudio_X28::~CAudio_X28()
	{
		fadeManagementEnabled = false;

		if (m_fadeManagingThread.joinable())
		{
			m_fadeManagingThread.join();
		}

		m_audios.destroy();

		m_device.release();

		::FreeLibrary(m_xaudio28);
	}

	bool CAudio_X28::hasAudioDevice() const
	{
		return m_hasAudioDevice;
	}

	bool CAudio_X28::init()
	{
		if (FAILED(m_device.masteringVoice->GetChannelMask(&m_device.channelMask)))
		{
			return false;
		}

		const auto nullAudio = std::make_shared<Audio_X28>(
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

	Audio::IDType CAudio_X28::create(Wave&& wave)
	{
		if (!wave)
		{
			return Audio::NullHandleID;
		}

		const auto audio = std::make_shared<Audio_X28>(
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

	void CAudio_X28::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}

	uint32 CAudio_X28::samplingRate(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samplingRate();
	}

	size_t CAudio_X28::samples(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samples();
	}

	void CAudio_X28::setLoop(const Audio::IDType handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setLoop(loop, loopBeginSample, loopEndSample);
	}

	bool CAudio_X28::play(const Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeinDuration.count()), 0.0);

		return m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PlayWithFade : AudioControlState::PlayImmediately,
			fadeSec);
	}

	void CAudio_X28::pause(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PauseWithFade : AudioControlState::PauseImmediately,
			fadeSec);
	}

	void CAudio_X28::stop(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::StopWithFade : AudioControlState::StopImmediately,
			fadeSec);
	}

	bool CAudio_X28::isPlaying(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->isPlaying();
	}

	bool CAudio_X28::isPaused(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->isPaused();
	}

	uint64 CAudio_X28::posSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->posSample();
	}

	uint64 CAudio_X28::streamPosSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->streamPosSample();
	}
	
	uint64 CAudio_X28::samplesPlayed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->samplesPlayed();
	}

	const Wave& CAudio_X28::getWave(const Audio::IDType handleID)
	{
		return m_audios[handleID]->getWave();
	}

	void CAudio_X28::setVolume(const Audio::IDType handleID, const std::pair<double, double>& volume)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setVolume(volume);
	}

	std::pair<double, double> CAudio_X28::getVolume(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getVolume();
	}

	void CAudio_X28::setSpeed(const Audio::IDType handleID, const double speed)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setSpeed(speed);
	}

	double CAudio_X28::getSpeed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getSpeed();
	}

	std::pair<double, double> CAudio_X28::getMinMaxSpeed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->getMinMaxSpeed();
	}

	bool CAudio_X28::updateFade()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		for (const auto& audio : m_audios)
		{
			audio.second->updateFadeManager();
		}

		return fadeManagementEnabled;
	}

	void CAudio_X28::fadeMasterVolume()
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
