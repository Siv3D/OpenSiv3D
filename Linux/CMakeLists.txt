cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig)

project(open_siv3d_linux CXX)
enable_language(C)

set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")

#set(CMAKE_BUILD_TYPE Release)

# In current version, Wayland and Mir are not supported.
set(_SIV3D_LINUX_WINDOW_API_X11 "Use X11 for window creation" ON)
# set(_SIV3D_LINUX_WINDOW_API_WAYLAND "Use Wayland for window creation" OFF)
# set(_SIV3D_LINUX_WINDOW_API_MIR "Use Mir for window creation" OFF)

if (_SIV3D_LINUX_WINDOW_API_X11)
	option(_SIV3D_LINUX_WINDOW_API_X11 "Use X11 for window creation" ON)
	option(_SIV3D_LINUX_WINDOW_API_WAYLAND "Use Wayland for window creation" OFF)
	option(_SIV3D_LINUX_WINDOW_API_MIR "Use Mir for window creation" OFF)
elseif (_SIV3D_LINUX_WINDOW_API_WAYLAND)
	option(_SIV3D_LINUX_WINDOW_API_X11 "Use X11 for window creation" OFF)
	option(_SIV3D_LINUX_WINDOW_API_WAYLAND "Use Wayland for window creation" ON)
	option(_SIV3D_LINUX_WINDOW_API_MIR "Use Mir for window creation" OFF)
elseif (_SIV3D_LINUX_WINDOW_API_MIR)
	option(_SIV3D_LINUX_WINDOW_API_X11 "Use X11 for window creation" OFF)
	option(_SIV3D_LINUX_WINDOW_API_WAYLAND "Use Wayland for window creation" OFF)
	option(_SIV3D_LINUX_WINDOW_API_MIR "Use Mir for window creation" ON)
endif()
configure_file(./Siv3D_Linux_GLFW_Window_API.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Siv3D_Linux_GLFW_Window_API.h)

pkg_check_modules(LIBSIV3D REQUIRED glib-2.0 gobject-2.0 gio-2.0 gl libpng libjpeg x11 xi xinerama xcursor xrandr)
include_directories(
	"/usr/include"

	"."
	"../Siv3D/Include"
	"../Siv3D/Source/ThirdParty/zstd"
	"../Siv3D/Source/ThirdParty/zstd/common"
	"../Siv3D/Source/ThirdParty/"

	${LIBSIV3D_INCLUDE_DIRS}
)

set(SOURCE_FILES
	"../Siv3D/Source/Siv3D/Base64/SivBase64.cpp"
	"../Siv3D/Source/Siv3D/BigFloat/SivBigFloat.cpp"
	"../Siv3D/Source/Siv3D/BigInt/SivBigInt.cpp"
	"../Siv3D/Source/Siv3D/BinaryReader/SivBinaryReader.cpp"
	"../Siv3D/Source/Siv3D/BinaryReader/CBinaryReader_Linux.cpp"
	"../Siv3D/Source/Siv3D/BinaryWriter/SivBinaryWriter.cpp"
	"../Siv3D/Source/Siv3D/BinaryWriter/CBinaryWriter_Linux.cpp"
	"../Siv3D/Source/Siv3D/ByteArray/CByteArray.cpp"
	"../Siv3D/Source/Siv3D/ByteArray/SivByteArray.cpp"
	"../Siv3D/Source/Siv3D/CharacterSet/SivCharacterSet.cpp"
	"../Siv3D/Source/Siv3D/Circle/SivCircle.cpp"
	"../Siv3D/Source/Siv3D/Color/SivColor.cpp"
	"../Siv3D/Source/Siv3D/Compression/SivCompression.cpp"
	"../Siv3D/Source/Siv3D/Console/CConsole.cpp"
	"../Siv3D/Source/Siv3D/Console/ConsoleFactory.cpp"
	"../Siv3D/Source/Siv3D/Console/SivConsole.cpp"
	"../Siv3D/Source/Siv3D/Cursor/CCursor_Linux.cpp"
	"../Siv3D/Source/Siv3D/Cursor/CursorFactory.cpp"
	"../Siv3D/Source/Siv3D/Cursor/SivCursor.cpp"
	"../Siv3D/Source/Siv3D/Date/SivDate.cpp"
	"../Siv3D/Source/Siv3D/DateTime/SivDateTime.cpp"
	"../Siv3D/Source/Siv3D/DragDrop/CDragDrop_Linux.cpp"
	"../Siv3D/Source/Siv3D/DragDrop/DragDropFactory.cpp"
	"../Siv3D/Source/Siv3D/DragDrop/SivDragDrop.cpp"
	"../Siv3D/Source/Siv3D/EngineDirectory/EngineDirectory.cpp"
	"../Siv3D/Source/Siv3D/FileSystem/SivFileSystem.cpp"
	"../Siv3D/Source/Siv3D/FileSystem/SivFileSystem_Linux.cpp"
	"../Siv3D/Source/Siv3D/Format/SivFormat.cpp"
	"../Siv3D/Source/Siv3D/FormatBool/SivFormatBool.cpp"
	"../Siv3D/Source/Siv3D/FormatFloat/SivFormatFloat.cpp"
	"../Siv3D/Source/Siv3D/FormatInt/SivFormatInt.cpp"
	"../Siv3D/Source/Siv3D/Graphics/D3D11/CGraphics_D3D11.cpp"
	"../Siv3D/Source/Siv3D/Graphics/D3D11/Device/D3D11Device.cpp"
	"../Siv3D/Source/Siv3D/Graphics/D3D11/RenderTarget/D3D11RenderTarget.cpp"
	"../Siv3D/Source/Siv3D/Graphics/D3D11/SwapChain/D3D11SwapChain.cpp"
	"../Siv3D/Source/Siv3D/Graphics/GL/CGraphics_GL.cpp"
	"../Siv3D/Source/Siv3D/Graphics/GraphicsFactory.cpp"
	"../Siv3D/Source/Siv3D/Graphics/SivGraphics.cpp"
	"../Siv3D/Source/Siv3D/HSV/SivHSV.cpp"
	"../Siv3D/Source/Siv3D/INIReader/CINIReader.cpp"
	"../Siv3D/Source/Siv3D/INIReader/SivINIReader.cpp"
	"../Siv3D/Source/Siv3D/Image/SivImage.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/BMP/ImageFormat_BMP.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/JPEG/ImageFormat_JPEG.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/PNG/ImageFormat_PNG.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/CImageFormat.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/ImageFormatFactory.cpp"
	"../Siv3D/Source/Siv3D/ImageFormat/SivImageFormat.cpp"
	"../Siv3D/Source/Siv3D/Key/SivKey.cpp"
	"../Siv3D/Source/Siv3D/Keyboard/CKeyboard_Linux.cpp"
	"../Siv3D/Source/Siv3D/Keyboard/KeyboardFactory.cpp"
	"../Siv3D/Source/Siv3D/Line/SivLine.cpp"
	"../Siv3D/Source/Siv3D/Logger/CLogger.cpp"
	"../Siv3D/Source/Siv3D/Logger/LoggerFactory.cpp"
	"../Siv3D/Source/Siv3D/Logger/SivLogger.cpp"
	"../Siv3D/Source/Siv3D/MD5/SivMD5.cpp"
	"../Siv3D/Source/Siv3D/MathParser/CMathParser.cpp"
	"../Siv3D/Source/Siv3D/MathParser/SivMathParser.cpp"
	"../Siv3D/Source/Siv3D/MemoryMapping/CMemoryMapping.cpp"
	"../Siv3D/Source/Siv3D/MemoryMapping/SivMemoryMapping.cpp"
	"../Siv3D/Source/Siv3D/Monitor/SivMonitor.cpp"
	"../Siv3D/Source/Siv3D/Mouse/CMouse_Linux.cpp"
	"../Siv3D/Source/Siv3D/Mouse/MouseFactory.cpp"
	"../Siv3D/Source/Siv3D/Mouse/SivMouse.cpp"
	"../Siv3D/Source/Siv3D/ParseFloat/SivParseFloat.cpp"
	"../Siv3D/Source/Siv3D/PerlinNoise/SivPerlinNoise.cpp"
	"../Siv3D/Source/Siv3D/Point/SivPoint.cpp"
	"../Siv3D/Source/Siv3D/Rectangle/SivRectangle.cpp"
	"../Siv3D/Source/Siv3D/Siv3DEngine.cpp"
	"../Siv3D/Source/Siv3D/Stopwatch/SivStopwatch.cpp"
	"../Siv3D/Source/Siv3D/String/SivString.cpp"
	"../Siv3D/Source/Siv3D/System/CSystem_Linux.cpp"
	"../Siv3D/Source/Siv3D/System/SystemFactory.cpp"
	"../Siv3D/Source/Siv3D/System/SivSystem.cpp"
	"../Siv3D/Source/Siv3D/CharacterEncoding/SivCharacterEncoding.cpp"
	"../Siv3D/Source/Siv3D/TextReader/CTextReader.cpp"
	"../Siv3D/Source/Siv3D/TextReader/CTextReader_Linux.cpp"
	"../Siv3D/Source/Siv3D/TextReader/SivTextReader.cpp"
	"../Siv3D/Source/Siv3D/TextWriter/CTextWriter.cpp"
	"../Siv3D/Source/Siv3D/TextWriter/SivTextWriter.cpp"
	"../Siv3D/Source/Siv3D/Threading/SivThreading.cpp"
	"../Siv3D/Source/Siv3D/Time/SivTime.cpp"
	"../Siv3D/Source/Siv3D/TimeProfiler/SivTimeProfiler.cpp"
	"../Siv3D/Source/Siv3D/Triangle/SivTriangle.cpp"
	"../Siv3D/Source/Siv3D/Vector2D/SivVector2D.cpp"
	"../Siv3D/Source/Siv3D/Vector3D/SivVector3D.cpp"
	"../Siv3D/Source/Siv3D/Vector4D/SivVector4D.cpp"
	"../Siv3D/Source/Siv3D/Window/CWindow_Linux.cpp"
	"../Siv3D/Source/Siv3D/Window/SivWindow.cpp"
	"../Siv3D/Source/Siv3D/Window/WindowFactory.cpp"
	"../Siv3D/Source/Siv3D/WritableMemoryMapping/CWritableMemoryMapping.cpp"
	"../Siv3D/Source/Siv3D/WritableMemoryMapping/SivWritableMemoryMapping.cpp"
	"../Siv3D/Source/Siv3D/XXHash/SivXXHash.cpp"

	"../Siv3D/Source/Siv3D/Siv3DMain_Linux.cpp"

	"../Siv3D/Source/ThirdParty/double-conversion/bignum-dtoa.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/bignum.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/cached-powers.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/diy-fp.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/double-conversion.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/fast-dtoa.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/fixed-dtoa.cc"
	"../Siv3D/Source/ThirdParty/double-conversion/strtod.cc"
	"../Siv3D/Source/ThirdParty/fmt/format.cc"
	"../Siv3D/Source/ThirdParty/md5/md5.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParser.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserBase.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserBytecode.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserCallback.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserDLL.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserError.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserInt.cpp"
	"../Siv3D/Source/ThirdParty/muparser/muParserTokenReader.cpp"
	"../Siv3D/Source/ThirdParty/zstd/common/entropy_common.c"
	"../Siv3D/Source/ThirdParty/zstd/common/error_private.c"
	"../Siv3D/Source/ThirdParty/zstd/common/fse_decompress.c"
	"../Siv3D/Source/ThirdParty/zstd/common/xxhash.c"
	"../Siv3D/Source/ThirdParty/zstd/common/zstd_common.c"
	"../Siv3D/Source/ThirdParty/zstd/compress/fse_compress.c"
	"../Siv3D/Source/ThirdParty/zstd/compress/huf_compress.c"
	"../Siv3D/Source/ThirdParty/zstd/compress/zstd_compress.c"
	"../Siv3D/Source/ThirdParty/zstd/decompress/huf_decompress.c"
	"../Siv3D/Source/ThirdParty/zstd/decompress/zstd_decompress.c"
	"../Siv3D/Source/ThirdParty/zstd/dictBuilder/divsufsort.c"
	"../Siv3D/Source/ThirdParty/zstd/dictBuilder/zdict.c"
	"../Siv3D/Source/ThirdParty/butteraugli/butteraugli.cc"
	"../Siv3D/Source/ThirdParty/guetzli/butteraugli_comparator.cc"
	"../Siv3D/Source/ThirdParty/guetzli/dct_double.cc"
	"../Siv3D/Source/ThirdParty/guetzli/debug_print.cc"
	"../Siv3D/Source/ThirdParty/guetzli/entropy_encode.cc"
	"../Siv3D/Source/ThirdParty/guetzli/fdct.cc"
	"../Siv3D/Source/ThirdParty/guetzli/gamma_correct.cc"
	"../Siv3D/Source/ThirdParty/guetzli/idct.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_data.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_data_decoder.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_data_encoder.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_data_reader.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_data_writer.cc"
	"../Siv3D/Source/ThirdParty/guetzli/jpeg_huffman_decode.cc"
	"../Siv3D/Source/ThirdParty/guetzli/output_image.cc"
	"../Siv3D/Source/ThirdParty/guetzli/preprocess_downsample.cc"
	"../Siv3D/Source/ThirdParty/guetzli/processor.cc"
	"../Siv3D/Source/ThirdParty/guetzli/quality.cc"
	"../Siv3D/Source/ThirdParty/guetzli/quantize.cc"
	"../Siv3D/Source/ThirdParty/guetzli/score.cc"

	# GLFW
	# common files
	"../Siv3D/Source/ThirdParty/GLFW/deps/glad.c"

	"../Siv3D/Source/ThirdParty/GLFW/src/context.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/init.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/input.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/monitor.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/vulkan.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/window.c"

	"../Siv3D/Source/ThirdParty/GLFW/src/linux_joystick.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/posix_time.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/posix_tls.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/xkb_unicode.c"
	"../Siv3D/Source/ThirdParty/GLFW/src/egl_context.c"
)

if (_SIV3D_LINUX_WINDOW_API_X11)
	set (SOURCE_FILES
		${SOURCE_FILES}
		"../Siv3D/Source/ThirdParty/GLFW/src/x11_init.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/x11_monitor.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/x11_window.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/glx_context.c"
	)
elseif (_SIV3D_LINUX_WINDOW_API_WAYLAND)
	set (SOURCE_FILES
		${SOURCE_FILES}
		"../Siv3D/Source/ThirdParty/GLFW/src/wl_init.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/wl_monitor.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/wl_window.c"
	)
elseif (_SIV3D_LINUX_WINDOW_API_MIR)
	set (SOURCE_FILES
		${SOURCE_FILES}
		"../Siv3D/Source/ThirdParty/GLFW/src/mir_init.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/mir_monitor.c"
		"../Siv3D/Source/ThirdParty/GLFW/src/mir_window.c"
	)
endif()

add_library(siv3d STATIC ${SOURCE_FILES})

target_link_libraries(siv3d
)

