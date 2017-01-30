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

# include "CCursor_Windows.hpp"
# include "CCursor_macOS.hpp"

namespace s3d
{
	ISiv3DCursor* ISiv3DCursor::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CCursor_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CCursor_macOS;
		
	# endif
	}
}

