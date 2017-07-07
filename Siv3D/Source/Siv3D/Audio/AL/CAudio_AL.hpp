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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../IAudio.hpp"

namespace s3d
{
	class CAudio_AL : public ISiv3DAudio
	{
	private:

	public:

		CAudio_AL();

		~CAudio_AL() override;
		
		bool hasAudioDevice() const override;

		bool init() override;

		Audio::IDType create(Wave&& wave) override;

		void release(Audio::IDType handleID) override;

		uint32 samplingRate(Audio::IDType handleID) override;

		size_t samples(Audio::IDType handleID) override;

		void setLoop(Audio::IDType handleID, bool loop, int64 loopBeginSample, int64 loopEndSample) override;

		bool play(Audio::IDType handleID, const SecondsF& fadeinDuration) override;

		void pause(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		void stop(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		uint64 posSample(Audio::IDType handleID) override;

		uint64 streamPosSample(Audio::IDType handleID) override;

		uint64 samplesPlayed(Audio::IDType handleID) override;

		void setVolume(Audio::IDType handleID, const std::pair<double, double>& volume) override;

		std::pair<double, double> getVolume(Audio::IDType handleID) override;

		void setSpeed(Audio::IDType handleID, double speed) override;

		double getSpeed(Audio::IDType handleID) override;

		std::pair<double, double> getMinMaxSpeed(Audio::IDType handleID) override;

		bool updateFade() override;

		void fadeMasterVolume() override;
	};
}

# endif
