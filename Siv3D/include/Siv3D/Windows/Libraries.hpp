//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
# pragma comment (lib, "crypt32")
# pragma comment (lib, "dinput8")
# pragma comment (lib, "dwmapi")
# pragma comment (lib, "dxguid")
# pragma comment (lib, "imm32")
# pragma comment (lib, "mfuuid")
# pragma comment (lib, "opengl32")
# pragma comment (lib, "Setupapi")
# pragma comment (lib, "version")
# pragma comment (lib, "winmm")
# pragma comment (lib, "Ws2_32")
# pragma comment (lib, "curl/libcurl" SIV3D_DEBUG_LIB_POSTFIX(-d))
# pragma comment (lib, "freetype/freetype" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "glew/glew32s" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "harfbuzz/harfbuzz" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libgif/libgif" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libjpeg-turbo/turbojpeg-static" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libogg/libogg" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libpng/libpng16" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libtiff/tiff" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "libvorbis/libvorbis_static" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libvorbis/libvorbisfile_static" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "libwebp/libwebp" SIV3D_DEBUG_LIB_POSTFIX(_debug))
# pragma comment (lib, "Oniguruma/Oniguruma" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "opencv/opencv_core451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opencv/opencv_imgcodecs451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opencv/opencv_imgproc451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opencv/opencv_objdetect451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opencv/opencv_photo451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opencv/opencv_videoio451" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "opus/opus" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "opus/opusfile" SIV3D_DEBUG_LIB_POSTFIX(_d))
# pragma comment (lib, "zlib/zlib" SIV3D_DEBUG_LIB_POSTFIX(d))
# pragma comment (lib, "Siv3D" SIV3D_DEBUG_LIB_POSTFIX(_d))

# if SIV3D_BUILD(DEBUG)
# pragma comment (lib, "boost/libboost_filesystem-vc142-mt-sgd-x64-1_74")
# else
# pragma comment (lib, "boost/libboost_filesystem-vc142-mt-s-x64-1_74")
# endif

# undef SIV3D_DEBUG_LIB_POSTFIX


extern "C"
{
	_declspec(selectany) _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	_declspec(selectany) _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
