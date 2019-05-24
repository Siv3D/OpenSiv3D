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

# pragma once
# include <Siv3D/Windows.hpp>
# include <XAudio2_7/XAudio2.h>
# include <XAudio2_7/XAudio2fx.h>
# include <XAudio2_7/X3DAudio.h>
# include <Siv3D/Wave.hpp>
# include <Audio/AudioControlManager.hpp>
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

		static constexpr size_t MaxVoiceShots = 32;

		Array<std::shared_ptr<SimpleVoice_X27>> m_voiceShots;

		bool m_is3D = false;

		bool m_initialized = false;

		void setFadeVolume(const double volume);

	public:

		Audio_X27() = default;

		Audio_X27(Wave&& wave, AudioDevice_X27* const device, const Optional<AudioLoopTiming>& loop, const double maxSpeed);

		~Audio_X27();

		bool isInitialized() const noexcept;

		const Wave& getWave() const;

		VoiceStream_X27& getStream();

		const VoiceStream_X27& getStream() const;

		void setPosSample(int64 posSample);

		bool changeState(const AudioControlState state, const double durationSec);

		AudioControlState getState() const;

		void playOneShot(double volume, double pitch);

		void stopAllShots();

		bool updateFade();
	};
}
