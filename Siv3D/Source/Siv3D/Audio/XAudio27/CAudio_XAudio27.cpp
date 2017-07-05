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

# include "CAudio_XAudio27.hpp"

namespace s3d
{
	CAudio_XAudio27::CAudio_XAudio27()
	{
		// [Siv3D ToDo]
	}

	CAudio_XAudio27::~CAudio_XAudio27()
	{
		// [Siv3D ToDo]
	}

	bool CAudio_XAudio27::hasAudioDevice() const
	{
		return m_hasAudioDevice;
	}

	bool CAudio_XAudio27::init()
	{
		// [Siv3D ToDo]
		return true;
	}

	Audio::IDType CAudio_XAudio27::create(Wave&& wave)
	{
		// [Siv3D ToDo]
		return Audio::NullHandleID;
	}

	void CAudio_XAudio27::release(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
	}

	bool CAudio_XAudio27::play(Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_XAudio27::pause(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}

	void CAudio_XAudio27::stop(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}

	uint64 CAudio_XAudio27::samplesPlayed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_XAudio27::streamPosSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	bool CAudio_XAudio27::updateFade()
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_XAudio27::fadeMasterVolume()
	{
		// [Siv3D ToDo]
	}
}

# endif
