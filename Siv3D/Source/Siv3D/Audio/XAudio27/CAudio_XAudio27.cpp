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

	}

	CAudio_XAudio27::~CAudio_XAudio27()
	{

	}

	bool CAudio_XAudio27::init()
	{

		return true;
	}

	Audio::IDType CAudio_XAudio27::create(const Wave& wave)
	{
		return Audio::NullHandleID;
	}

	void CAudio_XAudio27::release(const Audio::IDType handleID)
	{

	}
}

# endif
