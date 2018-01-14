//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

		static constexpr size_t MaxVoiceShots = 32;

		Array<std::shared_ptr<SimpleVoice_X28>> m_voiceShots;

		bool m_is3D = false;

		bool m_initialized = false;

		void setFadeVolume(const double volume);

	public:

		Audio_X28() = default;

		Audio_X28(Wave&& wave, AudioDevice_X28* const device, const Optional<AudioLoopTiming>& loop, const double maxSpeed);

		~Audio_X28();

		bool isInitialized() const noexcept;

		const Wave& getWave() const;

		VoiceStream_X28& getStream();

		const VoiceStream_X28& getStream() const;

		void setPosSample(int64 posSample);

		bool changeState(const AudioControlState state, const double durationSec);

		void playOneShot(double volume, double pitch);

		void stopAllShots();

		bool updateFade();
	};
}

# endif
