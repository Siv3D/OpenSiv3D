//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Siv3D/Platform.hpp"

# if !defined(SIV3D_TARGET_WINDOWS)
	# error
# endif

# if(_MSC_FULL_VER < 190023918)
	# error Visual Studio 2015 Update 2 以降が必要です | Visual Studio 2015 Update 2 or later is required
# endif
# pragma comment (linker, "/entry:\"wWinMainCRTStartup\"")

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)
	# ifdef _DEBUG
		# pragma comment (lib, "Windows(x64)/Siv3D_d")
	# else
		# pragma comment (lib, "Windows(x64)/Siv3D")
	# endif
# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)
	# ifdef _DEBUG
		# pragma comment (lib, "Windows(x86)/Siv3D_d")
	# else
		# pragma comment (lib, "Windows(x86)/Siv3D")
	# endif
# endif

# pragma comment (lib, "winmm")
