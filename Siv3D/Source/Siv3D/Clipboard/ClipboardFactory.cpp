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

# include "CClipboard_Windows.hpp"
# include "CClipboard_macOS.hpp"
# include "CClipboard_Linux.hpp"

namespace s3d
{
	ISiv3DClipboard* ISiv3DClipboard::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CClipboard_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CClipboard_macOS;
		
	# elif defined(SIV3D_TARGET_LINUX)

		return new CClipboard_Linux;

	# endif
	}
}

