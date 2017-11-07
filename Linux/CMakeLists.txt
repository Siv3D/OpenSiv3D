cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig)

project(OpenSiv3D_Linux CXX)
enable_language(C)

set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wno-unknown-pragmas -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

set(CMAKE_C_COMPILER "clang")
#set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-unknown-pragmas -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

#set(CMAKE_BUILD_TYPE Release)

#pkg_check_modules(LIBSIV3D REQUIRED glib-2.0 gobject-2.0 gio-2.0 gl libpng libturbojpeg x11 xi xinerama xcursor xrandr gl glu freetype2 openal)
include_directories(
	"/usr/include"

	"."
	"../Siv3D/include"
	"../Siv3D/src/ThirdParty/"

	${LIBSIV3D_INCLUDE_DIRS}
)

set(SOURCE_FILES
	"../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp"
	"../Siv3D/src/Siv3D/BigInt/CBigInt.cpp"
	"../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp"
	"../Siv3D/src/Siv3D/BoolFormat/SivBoolFormat.cpp"
	"../Siv3D/src/Siv3D/Byte/SivByte.cpp"
	"../Siv3D/src/Siv3D/FloatFormat/SivFloatFormat.cpp"
	"../Siv3D/src/Siv3D/Format/SivFormat.cpp"
	"../Siv3D/src/Siv3D/FormatLiteral/SivFormatLiteral.cpp"
	"../Siv3D/src/Siv3D/IntFormat/SivIntFormat.cpp"
	"../Siv3D/src/Siv3D/String/SivString.cpp"
	"../Siv3D/src/Siv3D/Threading/SivThreading.cpp"
	"../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp"
	"../Siv3D/src/Siv3DMain_Windows.cpp"
	"../Siv3D/src/Siv3DMain_macOS.cpp"
	"../Siv3D/src/Siv3DMain_Linux.cpp"

	"../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/bignum.cc"
	"../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc"
	"../Siv3D/src/ThirdParty/double-conversion/diy-fp.cc"
	"../Siv3D/src/ThirdParty/double-conversion/double-conversion.cc"
	"../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/strtod.cc"
	"../Siv3D/src/ThirdParty/fmt/format.cc"
)

add_library(Siv3D STATIC ${SOURCE_FILES})

target_link_libraries(Siv3D
)

