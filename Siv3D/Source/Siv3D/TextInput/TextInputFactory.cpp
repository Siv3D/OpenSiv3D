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

# include "CTextInput_Windows.hpp"
# include "CTextInput_macOS.hpp"

namespace s3d
{
	ISiv3DTextInput* ISiv3DTextInput::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CTextInput_Windows;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
		
		return new CTextInput_macOS;
		
	# endif
	}
}
