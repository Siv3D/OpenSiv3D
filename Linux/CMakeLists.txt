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
	"../Siv3D/src/Siv3D/Base64/SivBase64.cpp"
	"../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp"
	"../Siv3D/src/Siv3D/BigInt/CBigInt.cpp"
	"../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp"
	"../Siv3D/src/Siv3D/BinaryReader/CBinaryReader_Linux.cpp"
	"../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp"
	"../Siv3D/src/Siv3D/BinaryWriter/CBinaryWriter_Linux.cpp"
	"../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp"
	"../Siv3D/src/Siv3D/BoolFormat/SivBoolFormat.cpp"
	"../Siv3D/src/Siv3D/Byte/SivByte.cpp"
	"../Siv3D/src/Siv3D/ByteArray/CByteArray.cpp"
	"../Siv3D/src/Siv3D/ByteArray/SivByteArray.cpp"
	"../Siv3D/src/Siv3D/ByteArrayView/SivByteArrayView.cpp"
	"../Siv3D/src/Siv3D/Console/CConsole.cpp"
	"../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp"
	"../Siv3D/src/Siv3D/Console/SivConsole.cpp"
	"../Siv3D/src/Siv3D/Date/SivDate.cpp"
	"../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp"
	"../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp"
	"../Siv3D/src/Siv3D/FileSystem/SivFileSystem_Linux.cpp"
	"../Siv3D/src/Siv3D/FloatFormat/SivFloatFormat.cpp"
	"../Siv3D/src/Siv3D/Format/SivFormat.cpp"
	"../Siv3D/src/Siv3D/FormatLiteral/SivFormatLiteral.cpp"
	"../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp"
	"../Siv3D/src/Siv3D/IntFormat/SivIntFormat.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp"
	"../Siv3D/src/Siv3D/Logger/CLogger.cpp"
	"../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp"
	"../Siv3D/src/Siv3D/Logger/SivLogger.cpp"
	"../Siv3D/src/Siv3D/MD5/SivMD5.cpp"
	"../Siv3D/src/Siv3D/MemoryMapping/CMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/MemoryMapping/SivMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/MemoryWriter/CMemoryWriter.cpp"
	"../Siv3D/src/Siv3D/MemoryWriter/SivMemoryWriter.cpp"
	"../Siv3D/src/Siv3D/ParseBool/SivParseBool.cpp"
	"../Siv3D/src/Siv3D/ParseFloat/SivParseFloat.cpp"
	"../Siv3D/src/Siv3D/ParseInt/SivParseInt.cpp"
	"../Siv3D/src/Siv3D/Resource/SivResource.cpp"
	"../Siv3D/src/Siv3D/Stopwatch/SivStopwatch.cpp"
	"../Siv3D/src/Siv3D/System/CSystem_Linux.cpp"
	"../Siv3D/src/Siv3D/System/SivSystem.cpp"
	"../Siv3D/src/Siv3D/System/SystemFactory.cpp"
	"../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp"
	"../Siv3D/src/Siv3D/TextReader/CTextReader.cpp"
	"../Siv3D/src/Siv3D/TextReader/CTextReader_Linux.cpp"
	"../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp"
	"../Siv3D/src/Siv3D/TextWriter/CTextWriter.cpp"
	"../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp"
	"../Siv3D/src/Siv3D/Time/SivTime.cpp"
	"../Siv3D/src/Siv3D/TimeProfiler/SivTimeProfiler.cpp"
	"../Siv3D/src/Siv3D/WritableMemoryMapping/CWritableMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/WritableMemoryMapping/SivWritableMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/String/SivString.cpp"
	"../Siv3D/src/Siv3D/Threading/SivThreading.cpp"
	"../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp"

	"../Siv3D/src/Siv3D/Siv3DEngine.cpp"
	"../Siv3D/src/Siv3D/Siv3DMain_Linux.cpp"

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

