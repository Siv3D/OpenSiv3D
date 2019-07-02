//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Platform.hpp"
# if SIV3D_PLATFORM(WINDOWS)

#	pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#	pragma comment (lib, "Dwmapi")
#	pragma comment (lib, "Winmm")
#	pragma comment (lib, "imm32")
#	pragma comment (lib, "version")
#	pragma comment (lib, "Shlwapi")
#	pragma comment (lib, "mfuuid")
#	pragma comment (lib, "ws2_32")
#	pragma comment (lib, "strmiids")

#	if (SIV3D_DEBUG)

#		pragma comment (lib, "Siv3D_d")
#		pragma comment (lib, "zlib/zlib_d")
#		pragma comment (lib, "libpng/libpng16_d")
#		pragma comment (lib, "libjpeg-turbo/turbojpeg-static_d")
#		pragma comment (lib, "libwebp/libwebp_debug")
#		pragma comment (lib, "libogg/libogg_static_d")
#		pragma comment (lib, "libvorbis/libvorbis_d")
#		pragma comment (lib, "libvorbis/libvorbisfile_d")
#		pragma comment (lib, "opencv/opencv_core401d")
#		pragma comment (lib, "opencv/opencv_imgproc401d")
#		pragma comment (lib, "opencv/opencv_photo401d")
#		pragma comment (lib, "opencv/opencv_objdetect401d")
#		pragma comment (lib, "opencv/opencv_imgcodecs401d")
#		pragma comment (lib, "opencv/opencv_videoio401d")
#		pragma comment (lib, "freetype/freetype28MTd")
#		pragma comment (lib, "harfbuzz/harfbuzz_d")
#		pragma comment (lib, "angelscript/angelscriptd")
#		pragma comment (lib, "jumanpp/jpp_jumandic_d")
#		pragma comment (lib, "jumanpp/jpp_util_d")
#		pragma comment (lib, "jumanpp/jpp_rnn_d")
#		pragma comment (lib, "jumanpp/jpp_core_d")
#		pragma comment (lib, "jumanpp/jumanpp_v2_d")

# else

#		pragma comment (lib, "Siv3D")
#		pragma comment (lib, "zlib/zlib")
#		pragma comment (lib, "libpng/libpng16")
#		pragma comment (lib, "libjpeg-turbo/turbojpeg-static")
#		pragma comment (lib, "libwebp/libwebp")
#		pragma comment (lib, "libogg/libogg_static")
#		pragma comment (lib, "libvorbis/libvorbis")
#		pragma comment (lib, "libvorbis/libvorbisfile")
#		pragma comment (lib, "opencv/opencv_core401")
#		pragma comment (lib, "opencv/opencv_imgproc401")
#		pragma comment (lib, "opencv/opencv_photo401")
#		pragma comment (lib, "opencv/opencv_objdetect401")
#		pragma comment (lib, "opencv/opencv_imgcodecs401")
#		pragma comment (lib, "opencv/opencv_videoio401")
#		pragma comment (lib, "freetype/freetype28MT")
#		pragma comment (lib, "harfbuzz/harfbuzz")
#		pragma comment (lib, "angelscript/angelscript")
#		pragma comment (lib, "jumanpp/jpp_jumandic")
#		pragma comment (lib, "jumanpp/jpp_util")
#		pragma comment (lib, "jumanpp/jpp_rnn")
#		pragma comment (lib, "jumanpp/jpp_core")
#		pragma comment (lib, "jumanpp/jumanpp_v2")

#	endif

# endif
