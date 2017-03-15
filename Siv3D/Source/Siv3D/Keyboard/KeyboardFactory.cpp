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

# include "CKeyboard_Windows.hpp"
# include "CKeyboard_macOS.hpp"
# include "CKeyboard_Linux.hpp"

namespace s3d
{
	ISiv3DKeyboard* ISiv3DKeyboard::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CKeyboard_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CKeyboard_macOS;
		
	# elif defined(SIV3D_TARGET_LINUX)

		return new CKeyboard_Linux;

	# endif
	}
}

