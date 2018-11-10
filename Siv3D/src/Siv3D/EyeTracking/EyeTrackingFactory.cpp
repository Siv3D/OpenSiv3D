//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CEyeTracking_Windows.hpp"
# include "CEyeTracking_macOS.hpp"

namespace s3d
{
	ISiv3DEyeTracking* ISiv3DEyeTracking::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CEyeTracking_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
		
		return new CEyeTracking_macOS;

	# endif
	}
}

