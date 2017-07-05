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

# include "CAudio_Null.hpp"

namespace s3d
{
	CAudio_Null::CAudio_Null()
	{

	}

	CAudio_Null::~CAudio_Null()
	{

	}

	bool CAudio_Null::hasAudioDevice() const
	{
		return false;
	}

	bool CAudio_Null::init()
	{

		return true;
	}

	Audio::IDType CAudio_Null::create(Wave&& wave)
	{
		return Audio::NullHandleID;
	}

	void CAudio_Null::release(const Audio::IDType handleID)
	{

	}

	bool CAudio_Null::play(Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_Null::pause(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}

	void CAudio_Null::stop(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}

	uint64 CAudio_Null::samplesPlayed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_Null::streamPosSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	bool CAudio_Null::updateFade()
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_Null::fadeMasterVolume()
	{
		// [Siv3D ToDo]
	}
}

