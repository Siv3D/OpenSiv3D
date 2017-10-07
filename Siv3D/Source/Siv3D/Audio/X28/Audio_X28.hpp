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
# include <Siv3D/Wave.hpp>
# include "../AudioControlManager.hpp"
# include "AudioDevice_X28 .hpp"
# include "VoiceStream_X28.hpp"

namespace s3d
{
	class Audio_X28
	{
	private:

		AudioDevice_X28* m_device = nullptr;

		Wave m_wave;

		VoiceStream_X28 m_stream;

		AudioControlManager m_audioControl;

		bool m_is3D = false;

		bool m_initialized = false;

	public:

		Audio_X28() = default;

		Audio_X28(Wave&& wave, AudioDevice_X28* const device, const Optional<std::pair<int64, int64>>& loop, const double maxSpeed);

		~Audio_X28();

		bool isInitialized() const noexcept;

		uint32 samplingRate() const;

		size_t samples() const;

		void setLoop(const bool loop, const int64 loopBeginSample, const int64 loopEndSample);

		bool changeState(const AudioControlState state, const double durationSec);

		bool updateFadeManager();

		void setFadeVolume(const double volume);

		void setPosSample(int64 posSample);

		bool isPlaying() const;

		bool isPaused() const;

		uint64 posSample();

		uint64 streamPosSample() const;

		uint64 samplesPlayed();

		const Wave& getWave() const;

		void setVolume(const std::pair<double, double>& volume);

		std::pair<double, double> getVolume() const;

		void setSpeed(const double speed);

		double getSpeed() const;

		std::pair<double, double> getMinMaxSpeed() const;
	};
}

# endif
