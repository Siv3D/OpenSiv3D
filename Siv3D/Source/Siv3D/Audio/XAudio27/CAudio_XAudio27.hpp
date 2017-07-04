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
# if defined(SIV3D_TARGET_WINDOWS)

# include "../IAudio.hpp"

namespace s3d
{
	class CAudio_XAudio27 : public ISiv3DAudio
	{
	private:

	public:

		CAudio_XAudio27();

		~CAudio_XAudio27() override;

		bool init() override;

		Audio::IDType create(const Wave& wave) override;

		void release(Audio::IDType handleID) override;
	};
}

# endif
