//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>

# if SIV3D_BUILD(DEBUG)
#	define SIV3D_DEBUG_LIB_POSTFIX(s) #s
# else
#	define SIV3D_DEBUG_LIB_POSTFIX(s)
# endif

# pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
# pragma comment (lib, "dwmapi")
# pragma comment (lib, "winmm")
# pragma comment (lib, "shcore")
# pragma comment (lib, "opengl32")
# pragma comment (lib, "version")
# pragma comment (lib, "Siv3D" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libpng/libpng16" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "zlib/zlib" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "glew/glew32s" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "Oniguruma/Oniguruma" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "AGG/AGG" SIV3D_DEBUG_LIB_POSTFIX(_d))

# undef SIV3D_DEBUG_LIB_POSTFIX
