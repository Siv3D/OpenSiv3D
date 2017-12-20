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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Audio.hpp>

namespace s3d
{
	class ISiv3DAudio
	{
	public:

		static ISiv3DAudio* Create();

		virtual ~ISiv3DAudio() = default;

		virtual bool init() = 0;

		virtual bool hasAudioDevice() const = 0;

		virtual AudioID create(Wave&& wave) = 0;

		virtual void release(AudioID handleID) = 0;

		virtual uint32 samplingRate(AudioID handleID) = 0;

		virtual size_t samples(AudioID handleID) = 0;

		virtual void setLoop(AudioID handleID, bool loop, int64 loopBeginSample, int64 loopEndSample) = 0;

		virtual bool play(AudioID handleID, const SecondsF& fadeinDuration) = 0;

		virtual void pause(AudioID handleID, const SecondsF& fadeoutDuration) = 0;

		virtual void stop(AudioID handleID, const SecondsF& fadeoutDuration) = 0;

		virtual bool isPlaying(AudioID handleID) = 0;

		virtual bool isPaused(AudioID handleID) = 0;

		virtual uint64 posSample(AudioID handleID) = 0;

		virtual uint64 streamPosSample(AudioID handleID) = 0;

		virtual uint64 samplesPlayed(AudioID handleID) = 0;

		virtual const Wave& getWave(AudioID handleID) = 0;

		virtual void setVolume(AudioID handleID, const std::pair<double, double>& volume) = 0;

		virtual std::pair<double, double> getVolume(AudioID handleID) = 0;

		virtual void setSpeed(AudioID handleID, double speed) = 0;

		virtual double getSpeed(AudioID handleID) = 0;

		virtual std::pair<double, double> getMinMaxSpeed(AudioID handleID) = 0;

		virtual bool updateFade() = 0;

		virtual void fadeMasterVolume() = 0;
	};
}
