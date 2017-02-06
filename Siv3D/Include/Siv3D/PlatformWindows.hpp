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

# pragma once
# include "Siv3D/Platform.hpp"

# if !defined(SIV3D_TARGET_WINDOWS)

	# error

# endif

# if(_MSC_FULL_VER < 190024210)

	# error Visual Studio 2015 Update 3 以降が必要です | Visual Studio 2015 Update 3 or later is required

# endif

# pragma comment (linker, "/entry:\"wWinMainCRTStartup\"")

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	# ifdef _DEBUG

		# pragma comment (lib, "Windows(x64)/Siv3D_d")
		# pragma comment (lib, "Windows(x64)/zlib/zlib_d")
		# pragma comment (lib, "Windows(x64)/libpng/libpng16_d")
		# pragma comment (lib, "Windows(x64)/libjpeg-turbo/turbojpeg-static_d")

	# else

		# pragma comment (lib, "Windows(x64)/Siv3D")
		# pragma comment (lib, "Windows(x64)/zlib/zlib")
		# pragma comment (lib, "Windows(x64)/libpng/libpng16")
		# pragma comment (lib, "Windows(x64)/libjpeg-turbo/turbojpeg-static")

	# endif

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	# ifdef _DEBUG

		# pragma comment (lib, "Windows(x86)/Siv3D_d")
		# pragma comment (lib, "Windows(x86)/zlib/zlib_d")
		# pragma comment (lib, "Windows(x86)/libpng/libpng16_d")
		# pragma comment (lib, "Windows(x86)/libjpeg-turbo/turbojpeg-static_d")

	# else

		# pragma comment (lib, "Windows(x86)/Siv3D")
		# pragma comment (lib, "Windows(x86)/zlib/zlib")
		# pragma comment (lib, "Windows(x86)/libpng/libpng16")
		# pragma comment (lib, "Windows(x86)/libjpeg-turbo/turbojpeg-static")

	# endif

# endif

# pragma comment (lib, "winmm")
