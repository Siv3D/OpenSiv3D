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

	bool CAudio_AL::init()
	{

		return true;
	}
}

# endif
