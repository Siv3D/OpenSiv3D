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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CAudio_AL.hpp"

namespace s3d
{
	CAudio_AL::CAudio_AL()
	{

	}

	CAudio_AL::~CAudio_AL()
	{

	}

	bool CAudio_AL::hasAudioDevice() const
	{
		// [Siv3D ToDo]
		return true;
	}

	bool CAudio_AL::init()
	{

		return true;
	}

	Audio::IDType CAudio_AL::create(Wave&& wave)
	{
		return Audio::NullHandleID;
	}

	void CAudio_AL::release(const Audio::IDType handleID)
	{

	}

	uint32 CAudio_AL::samplingRate(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	size_t CAudio_AL::samples(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	void CAudio_AL::setLoop(const Audio::IDType handleID, const bool loop, const int64 loopBeginSample, const int64 loopEndSample)
	{
		// [Siv3D ToDo]
	}

	bool CAudio_AL::play(Audio::IDType handleID, const SecondsF& fadeinDuration)
	{
		// [Siv3D ToDo]
		return true;
	}
	
	void CAudio_AL::pause(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}
	
	void CAudio_AL::stop(Audio::IDType handleID, const SecondsF& fadeoutDuration)
	{
		// [Siv3D ToDo]
	}

	uint64 CAudio_AL::posSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_AL::streamPosSample(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_AL::samplesPlayed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	void CAudio_AL::setVolume(const Audio::IDType handleID, const std::pair<double, double>& volume)
	{
		// [Siv3D ToDo]
	}

	std::pair<double, double> CAudio_AL::getVolume(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
	}

	void CAudio_AL::setSpeed(const Audio::IDType handleID, const double speed)
	{
		// [Siv3D ToDo]
	}

	double CAudio_AL::getSpeed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	std::pair<double, double> CAudio_AL::getMinMaxSpeed(const Audio::IDType handleID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
	}

	bool CAudio_AL::updateFade()
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_AL::fadeMasterVolume()
	{
		// [Siv3D ToDo]
	}
}

# endif
