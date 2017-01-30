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

# include "CMouse_Windows.hpp"
# include "CMouse_macOS.hpp"

namespace s3d
{
	ISiv3DMouse* ISiv3DMouse::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CMouse_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CMouse_macOS;
		
	# endif
	}
}

