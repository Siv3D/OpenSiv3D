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

	AudioID CAudio_Null::create(Wave&&)
	{
		return AudioID::NullAsset();
	}

	void CAudio_Null::release(const AudioID)
	{

	}

	uint32 CAudio_Null::samplingRate(const AudioID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	size_t CAudio_Null::samples(const AudioID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	void CAudio_Null::setLoop(const AudioID, const bool, const int64, const int64)
	{
		// [Siv3D ToDo]
	}

	bool CAudio_Null::play(const AudioID, const SecondsF&)
	{
		// [Siv3D ToDo]
		return true;
	}

	void CAudio_Null::pause(const AudioID, const SecondsF&)
	{
		// [Siv3D ToDo]
	}

	void CAudio_Null::stop(const AudioID, const SecondsF&)
	{
		// [Siv3D ToDo]
	}

	void CAudio_Null::playOneShot(AudioID, double, double)
	{
		// [Siv3D ToDo]
	}

	void CAudio_Null::stopAllShots(AudioID)
	{
		// [Siv3D ToDo]
	}

	bool CAudio_Null::isPlaying(const AudioID)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CAudio_Null::isPaused(const AudioID)
	{
		// [Siv3D ToDo]
		return false;
	}

	uint64 CAudio_Null::posSample(const AudioID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_Null::streamPosSample(const AudioID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	uint64 CAudio_Null::samplesPlayed(const AudioID)
	{
		// [Siv3D ToDo]
		return 0;
	}

	const Wave& CAudio_Null::getWave(const AudioID)
	{
		// [Siv3D ToDo]
		static Wave wave;
		return wave;
	}

	void CAudio_Null::setVolume(const AudioID, const std::pair<double, double>&)
	{
		// [Siv3D ToDo]
	}

	std::pair<double, double> CAudio_Null::getVolume(const AudioID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
	}

	void CAudio_Null::setSpeed(const AudioID, const double)
	{
		// [Siv3D ToDo]
	}

	double CAudio_Null::getSpeed(const AudioID)
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	std::pair<double, double> CAudio_Null::getMinMaxSpeed(const AudioID)
	{
		// [Siv3D ToDo]
		return{ 1.0,1.0 };
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

