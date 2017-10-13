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

# if(_MSC_FULL_VER < 191025017)

	# error Visual Studio 2017 が必要です | Visual Studio 2017 or later is required

# endif

# pragma comment (linker, "/entry:\"wWinMainCRTStartup\"")

# if defined _M_IX86

	# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

# elif defined _M_X64

	# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

# endif

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	# ifdef _DEBUG

		# pragma comment (lib, "Windows(x64)/Siv3D_d")
		# pragma comment (lib, "Windows(x64)/zlib/zlib_d")
		# pragma comment (lib, "Windows(x64)/libpng/libpng16_d")
		# pragma comment (lib, "Windows(x64)/libjpeg-turbo/turbojpeg-static_d")
		# pragma comment (lib, "Windows(x64)/freetype/freetype28MTd")
		# pragma comment (lib, "Windows(x64)/harfbuzz/harfbuzz_d")
		# pragma comment (lib, "Windows(x64)/angelscript/angelscript64d")

	# else

		# pragma comment (lib, "Windows(x64)/Siv3D")
		# pragma comment (lib, "Windows(x64)/zlib/zlib")
		# pragma comment (lib, "Windows(x64)/libpng/libpng16")
		# pragma comment (lib, "Windows(x64)/libjpeg-turbo/turbojpeg-static")
		# pragma comment (lib, "Windows(x64)/freetype/freetype28MT")
		# pragma comment (lib, "Windows(x64)/harfbuzz/harfbuzz")
		# pragma comment (lib, "Windows(x64)/angelscript/angelscript64")

	# endif

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	# ifdef _DEBUG

		# pragma comment (lib, "Windows(x86)/Siv3D_d")
		# pragma comment (lib, "Windows(x86)/zlib/zlib_d")
		# pragma comment (lib, "Windows(x86)/libpng/libpng16_d")
		# pragma comment (lib, "Windows(x86)/libjpeg-turbo/turbojpeg-static_d")
		# pragma comment (lib, "Windows(x86)/freetype/freetype28MTd")
		# pragma comment (lib, "Windows(x86)/harfbuzz/harfbuzz_d")
		# pragma comment (lib, "Windows(x86)/angelscript/angelscriptd")

	# else

		# pragma comment (lib, "Windows(x86)/Siv3D")
		# pragma comment (lib, "Windows(x86)/zlib/zlib")
		# pragma comment (lib, "Windows(x86)/libpng/libpng16")
		# pragma comment (lib, "Windows(x86)/libjpeg-turbo/turbojpeg-static")
		# pragma comment (lib, "Windows(x86)/freetype/freetype28MT")
		# pragma comment (lib, "Windows(x86)/harfbuzz/harfbuzz")
		# pragma comment (lib, "Windows(x86)/angelscript/angelscript")

	# endif

# endif

# pragma comment (lib, "winmm")
# pragma comment (lib, "Dwmapi")
# pragma comment (lib, "imm32")
# pragma comment (lib, "Shlwapi")
# pragma comment (lib, "mfuuid")
