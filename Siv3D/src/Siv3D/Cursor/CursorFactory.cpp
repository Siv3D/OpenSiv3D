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

# include "CCursor_Windows.hpp"
# include "CCursor_macOS.hpp"
# include "CCursor_Linux.hpp"

namespace s3d
{
	ISiv3DCursor* ISiv3DCursor::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return new CCursor_Windows;
		
	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CCursor_macOS;

	# elif defined(SIV3D_TARGET_LINUX)

		return new CCursor_Linux;

	# endif
	}
}

