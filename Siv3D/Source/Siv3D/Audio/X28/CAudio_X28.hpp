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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN8
# define  NTDDI_VERSION NTDDI_WIN8
# include <Windows.h>
# include <XAudio2.h>
# include <XAudio2fx.h>
# include <X3DAudio.h>
# include "../IAudio.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"
# include "Audio_X28.hpp"

namespace s3d
{
	class CAudio_X28 : public ISiv3DAudio
	{
	private:

		HINSTANCE m_xaudio28 = nullptr;

		decltype(XAudio2Create)* p_XAudio2Create = nullptr;

		bool m_hasAudioDevice = false;

		AudioDevice_X28 m_device;

		double m_masterVolume = 1.0;

		AssetHandleManager<Audio::IDType, std::shared_ptr<Audio_X28>> m_audios{ S3DSTR("Audio") };

		static std::atomic_bool fadeManagementEnabled;

		std::thread m_fadeManagingThread;

		std::mutex m_mutex;

	public:

		CAudio_X28();

		~CAudio_X28() override;

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

		uint64 posSample(Audio::IDType handleID) override;

		uint64 streamPosSample(Audio::IDType handleID) override;

		uint64 samplesPlayed(Audio::IDType handleID) override;

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
