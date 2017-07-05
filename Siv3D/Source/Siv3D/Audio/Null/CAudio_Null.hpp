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

# include "../IAudio.hpp"

namespace s3d
{
	class CAudio_Null : public ISiv3DAudio
	{
	private:

	public:

		CAudio_Null();

		~CAudio_Null() override;

		bool hasAudioDevice() const override;

		bool init() override;

		Audio::IDType create(Wave&& wave) override;

		void release(Audio::IDType handleID) override;

		bool play(Audio::IDType handleID, const SecondsF& fadeinDuration) override;

		void pause(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		void stop(Audio::IDType handleID, const SecondsF& fadeoutDuration) override;

		uint64 samplesPlayed(Audio::IDType handleID) override;

		uint64 streamPosSample(Audio::IDType handleID) override;

		bool updateFade() override;

		void fadeMasterVolume() override;
	};
}

