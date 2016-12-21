cmake_minimum_required(VERSION 2.8)

project(open_siv3d_linux CXX)

set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")

#set(CMAKE_BUILD_TYPE Release)

include_directories(
	"/usr/include"
	"./Siv3D/Include"
	"/usr/include/glib-2.0"
	"/usr/lib/glib-2.0/include"
)

add_library(siv3d STATIC
	"./Siv3D/Source/Siv3D/BigFloat/SivBigFloat.cpp"
	"./Siv3D/Source/Siv3D/BigInt/SivBigInt.cpp"
	"./Siv3D/Source/Siv3D/BinaryReader/SivBinaryReader.cpp"
	"./Siv3D/Source/Siv3D/BinaryReader/CBinaryReader_linux.cpp"
	"./Siv3D/Source/Siv3D/BinaryWriter/SivBinaryWriter.cpp"
	"./Siv3D/Source/Siv3D/BinaryWriter/CBinaryWriter_linux.cpp"
	"./Siv3D/Source/Siv3D/ByteArray/CByteArray.cpp"
	"./Siv3D/Source/Siv3D/ByteArray/SivByteArray.cpp"
	"./Siv3D/Source/Siv3D/CharacterSet/SivCharacterSet.cpp"
	"./Siv3D/Source/Siv3D/Color/SivColor.cpp"
	"./Siv3D/Source/Siv3D/Compression/SivCompression.cpp"
	"./Siv3D/Source/Siv3D/Console/CConsole.cpp"
	"./Siv3D/Source/Siv3D/Console/ConsoleFactory.cpp"
	"./Siv3D/Source/Siv3D/Console/SivConsole.cpp"
	"./Siv3D/Source/Siv3D/Date/SivDate.cpp"
	"./Siv3D/Source/Siv3D/DateTime/SivDateTime.cpp"
	"./Siv3D/Source/Siv3D/FileSystem/SivFileSystem.cpp"
	"./Siv3D/Source/Siv3D/FileSystem/SivFileSystem_Linux.cpp"
	"./Siv3D/Source/Siv3D/Format/SivFormat.cpp"
	"./Siv3D/Source/Siv3D/FormatFloat/SivFormatFloat.cpp"
	"./Siv3D/Source/Siv3D/FormatInt/SivFormatInt.cpp"
	"./Siv3D/Source/Siv3D/HSV/SivHSV.cpp"
	"./Siv3D/Source/Siv3D/Image/SivImage.cpp"
	"./Siv3D/Source/Siv3D/Logger/CLogger.cpp"
	"./Siv3D/Source/Siv3D/Logger/LoggerFactory.cpp"
	"./Siv3D/Source/Siv3D/Logger/SivLogger.cpp"
	"./Siv3D/Source/Siv3D/MemoryMapping/CMemoryMapping.cpp"
	"./Siv3D/Source/Siv3D/MemoryMapping/SivMemoryMapping.cpp"
	"./Siv3D/Source/Siv3D/ParseFloat/SivParseFloat.cpp"
	"./Siv3D/Source/Siv3D/PerlinNoise/SivPerlinNoise.cpp"
	"./Siv3D/Source/Siv3D/Point/SivPoint.cpp"
	"./Siv3D/Source/Siv3D/Siv3DEngine.cpp"
	"./Siv3D/Source/Siv3D/Stopwatch/SivStopwatch.cpp"
	"./Siv3D/Source/Siv3D/String/SivString.cpp"
	"./Siv3D/Source/Siv3D/System/CSystem.cpp"
	"./Siv3D/Source/Siv3D/System/SystemFactory.cpp"
	"./Siv3D/Source/Siv3D/System/SivSystem.cpp"
	"./Siv3D/Source/Siv3D/TextEncoding/SivTextEncoding.cpp"
	"./Siv3D/Source/Siv3D/TextReader/CTextReader.cpp"
	"./Siv3D/Source/Siv3D/TextReader/SivTextReader.cpp"
	"./Siv3D/Source/Siv3D/TextWriter/CTextWriter.cpp"
	"./Siv3D/Source/Siv3D/TextWriter/SivTextWriter.cpp"
	"./Siv3D/Source/Siv3D/Thread/SivThread.cpp"
	"./Siv3D/Source/Siv3D/Time/SivTime.cpp"
	"./Siv3D/Source/Siv3D/TimeProfiler/SivTimeProfiler.cpp"
	"./Siv3D/Source/Siv3D/Vector2D/SivVector2D.cpp"
	"./Siv3D/Source/Siv3D/Vector3D/SivVector3D.cpp"
	"./Siv3D/Source/Siv3D/Vector4D/SivVector4D.cpp"
	"./Siv3D/Source/Siv3D/Window/CWindow_Linux.cpp"
	"./Siv3D/Source/Siv3D/Window/SivWindow.cpp"
	"./Siv3D/Source/Siv3D/Window/WindowFactory.cpp"
	"./Siv3D/Source/Siv3D/WritableMemoryMapping/CWritableMemoryMapping.cpp"
	"./Siv3D/Source/Siv3D/WritableMemoryMapping/SivWritableMemoryMapping.cpp"

	"./Siv3D/Source/ThirdParty/double-conversion/bignum-dtoa.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/bignum.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/cached-powers.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/diy-fp.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/double-conversion.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/fast-dtoa.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/fixed-dtoa.cc"
	"./Siv3D/Source/ThirdParty/double-conversion/strtod.cc"
	"./Siv3D/Source/ThirdParty/fmt/format.cc"
	"./Siv3D/Source/ThirdParty/zstd/common/entropy_common.c"
	"./Siv3D/Source/ThirdParty/zstd/common/error_private.c"
	"./Siv3D/Source/ThirdParty/zstd/common/fse_decompress.c"
	"./Siv3D/Source/ThirdParty/zstd/common/xxhash.c"
	"./Siv3D/Source/ThirdParty/zstd/common/zstd_common.c"
	"./Siv3D/Source/ThirdParty/zstd/compress/fse_compress.c"
	"./Siv3D/Source/ThirdParty/zstd/compress/huf_compress.c"
	"./Siv3D/Source/ThirdParty/zstd/compress/zbuff_compress.c"
	"./Siv3D/Source/ThirdParty/zstd/compress/zstd_compress.c"
	"./Siv3D/Source/ThirdParty/zstd/decompress/huf_decompress.c"
	"./Siv3D/Source/ThirdParty/zstd/decompress/zbuff_decompress.c"
	"./Siv3D/Source/ThirdParty/zstd/decompress/zstd_decompress.c"
	"./Siv3D/Source/ThirdParty/zstd/dictBuilder/divsufsort.c"
	"./Siv3D/Source/ThirdParty/zstd/dictBuilder/zdict.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v01.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v02.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v03.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v04.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v05.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v06.c"
	"./Siv3D/Source/ThirdParty/zstd/legacy/zstd_v07.c"

	"./Siv3D/Source/Siv3D/Siv3DMain_Linux.cpp"
)

target_link_libraries(siv3d
)

