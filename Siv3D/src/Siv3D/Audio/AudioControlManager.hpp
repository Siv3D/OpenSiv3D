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
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	enum class AudioControlState
	{
		PlayImmediately,

		PlayWithFade,

		PauseImmediately,

		PauseWithFade,

		StopImmediately,

		StopWithFade,
	};

	enum class VoiceState
	{
		Ready,

		Waiting,

		Done,

		EndOfStream,
	};

	struct AudioLoopTiming
	{
		int64 beginPos = 0;

		int64 endPos = 0;

		AudioLoopTiming() = default;

		constexpr AudioLoopTiming(int64 _beginPos, int64 _endPos) noexcept
			: beginPos(_beginPos)
			, endPos(_endPos) {}
	};

	struct AudioControlManager
	{
		Stopwatch m_stopwatch;

		double m_durationSec = 0.0;

		double m_currentVolume = 0.0;

		VoiceState voiceState = VoiceState::Ready;

		AudioControlState m_state = AudioControlState::StopImmediately;

		bool m_seekBegin = false;
	};
}
