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
# include "CAudio_XAudio28.hpp"
# include "../../EngineUtility.hpp"

namespace s3d
{
	std::atomic_bool CAudio_XAudio28::fadeManagementEnabled{ true };

	namespace detail
	{
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

	bool CAudio_XAudio28::IsAvalibale()
	{
		if (HINSTANCE xaudio28 = ::LoadLibraryW(L"xaudio2_8.dll"))
		{
			::FreeLibrary(xaudio28);

			return true;
		}

		return false;
	}

	CAudio_XAudio28::CAudio_XAudio28()
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

	CAudio_XAudio28::~CAudio_XAudio28()
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

	bool CAudio_XAudio28::hasAudioDevice() const
	{
		return m_hasAudioDevice;
	}

	bool CAudio_XAudio28::init()
	{
		if (FAILED(m_device.masteringVoice->GetChannelMask(&m_device.channelMask)))
		{
			return false;
		}

		const auto nullAudio = std::make_shared<Audio_XAudio28>(
			Wave(22050, WaveSample::Zero()),
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

	Audio::IDType CAudio_XAudio28::create(Wave&& wave)
	{
		if (!wave)
		{
			return Audio::NullHandleID;
		}

		const auto audio = std::make_shared<Audio_XAudio28>(
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

	void CAudio_XAudio28::release(const Audio::IDType handleID)
	{
		m_audios.erase(handleID);
	}

	uint32 CAudio_XAudio28::samplingRate(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samplingRate();
	}

	size_t CAudio_XAudio28::samples(const Audio::IDType handleID)
	{
		return m_audios[handleID]->samples();
	}

	void CAudio_XAudio28::setLoop(const Audio::IDType handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_audios[handleID]->setLoop(loop, loopBeginSample, loopEndSample);
	}

	bool CAudio_XAudio28::play(const Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeinDuration.count()), 0.0);

		return m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PlayWithFade : AudioControlState::PlayImmediately,
			fadeSec);
	}

	void CAudio_XAudio28::pause(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::PauseWithFade : AudioControlState::PauseImmediately,
			fadeSec);
	}

	void CAudio_XAudio28::stop(const Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		const double fadeSec = std::max(static_cast<double>(fadeoutDuration.count()), 0.0);

		m_audios[handleID]->changeState(
			fadeSec > 0.0 ? AudioControlState::StopWithFade : AudioControlState::StopImmediately,
			fadeSec);
	}

	uint64 CAudio_XAudio28::posSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->posSample();
	}

	uint64 CAudio_XAudio28::streamPosSample(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->streamPosSample();
	}
	
	uint64 CAudio_XAudio28::samplesPlayed(const Audio::IDType handleID)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_audios[handleID]->samplesPlayed();
	}

	bool CAudio_XAudio28::updateFade()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		for (const auto& audio : m_audios)
		{
			audio.second->updateFadeManager();
		}

		return fadeManagementEnabled;
	}

	void CAudio_XAudio28::fadeMasterVolume()
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
