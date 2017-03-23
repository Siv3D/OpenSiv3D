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

# include "CWindow_Windows.hpp"
# include "CWindow_macOS.hpp"

namespace s3d
{
	ISiv3DWindow* ISiv3DWindow::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CWindow_Windows;

	# elif defined(SIV3D_TARGET_MACOS)

		return new CWindow_macOS;

	# endif
	}
}

