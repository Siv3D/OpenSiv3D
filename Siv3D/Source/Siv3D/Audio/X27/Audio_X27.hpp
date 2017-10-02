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
# include "../../../ThirdParty/XAudio2_7/XAudio2.h"
# include "../../../ThirdParty/XAudio2_7/XAudio2fx.h"
# include "../../../ThirdParty/XAudio2_7/X3DAudio.h"
# include <Siv3D/Wave.hpp>
# include "../AudioControlManager.hpp"
# include "AudioDevice_X27 .hpp"
# include "VoiceStream_X27.hpp"

namespace s3d
{
	class Audio_X27
	{
	private:

		AudioDevice_X27* m_device = nullptr;

		Wave m_wave;

		VoiceStream_X27 m_stream;

		AudioControlManager m_audioControl;

		bool m_is3D = false;

		bool m_initialized = false;

	public:

		Audio_X27() = default;

		Audio_X27(Wave&& wave, AudioDevice_X27* const device, const Optional<std::pair<int64, int64>>& loop, const double maxSpeed);

		~Audio_X27();

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
