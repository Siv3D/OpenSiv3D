﻿//-----------------------------------------------
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

		virtual Audio::IDType create(Wave&& wave) = 0;

		virtual void release(Audio::IDType handleID) = 0;

		virtual uint32 samplingRate(Audio::IDType handleID) = 0;

		virtual size_t samples(Audio::IDType handleID) = 0;

		virtual void setLoop(Audio::IDType handleID, bool loop, int64 loopBeginSample, int64 loopEndSample) = 0;

		virtual bool play(Audio::IDType handleID, const SecondsF& fadeinDuration) = 0;

		virtual void pause(Audio::IDType handleID, const SecondsF& fadeoutDuration) = 0;

		virtual void stop(Audio::IDType handleID, const SecondsF& fadeoutDuration) = 0;

		virtual bool isPlaying(Audio::IDType handleID) = 0;

		virtual bool isPaused(Audio::IDType handleID) = 0;

		virtual uint64 posSample(Audio::IDType handleID) = 0;

		virtual uint64 streamPosSample(Audio::IDType handleID) = 0;

		virtual uint64 samplesPlayed(Audio::IDType handleID) = 0;

		virtual const Wave& getWave(Audio::IDType handleID) = 0;

		virtual void setVolume(Audio::IDType handleID, const std::pair<double, double>& volume) = 0;

		virtual std::pair<double, double> getVolume(Audio::IDType handleID) = 0;

		virtual void setSpeed(Audio::IDType handleID, double speed) = 0;

		virtual double getSpeed(Audio::IDType handleID) = 0;

		virtual std::pair<double, double> getMinMaxSpeed(Audio::IDType handleID) = 0;

		virtual bool updateFade() = 0;

		virtual void fadeMasterVolume() = 0;
	};
}
