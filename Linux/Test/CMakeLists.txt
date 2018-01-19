cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig)

project(Siv3D_Test CXX)
enable_language(C)

set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

#set(CMAKE_BUILD_TYPE Release)

#add_definitions(-D)

include_directories(
	"/usr/include"
	"../../Siv3D/include"
	"../../Siv3D/include/ThirdParty"
)

link_directories(
	"/usr/lib"
)

add_executable(Siv3D_Test
	"../../Siv3D-Test/Main.cpp"
	"../../Siv3D-Test/Test/Test.cpp"

#	"../../Siv3D-Test/Test/TestAlignedMemory.cpp"
#	"../../Siv3D-Test/Test/TestArray.cpp"
#	"../../Siv3D-Test/Test/TestBase64.cpp"
#	"../../Siv3D-Test/Test/TestCharacterSet.cpp"
#	"../../Siv3D-Test/Test/TestConcept.cpp"
#	"../../Siv3D-Test/Test/TestFileSystem.cpp"
#	"../../Siv3D-Test/Test/TestFormatBool.cpp"
#	"../../Siv3D-Test/Test/TestFormatFloat.cpp"
#	"../../Siv3D-Test/Test/TestFormatInt.cpp"
#	"../../Siv3D-Test/Test/TestMath.cpp"
#	"../../Siv3D-Test/Test/TestNamedParameter.cpp"
#	"../../Siv3D-Test/Test/TestOptional.cpp"
#	"../../Siv3D-Test/Test/TestStep.cpp"
#	"../../Siv3D-Test/Test/TestString.cpp"
#	"../../Siv3D-Test/Test/TestTypes.cpp"
#	"../../Siv3D-Test/Test/TestUtility.cpp"

#	"../../Siv3D-Test/Test/Siv3DTest_Linux.cpp"

#	"../../Siv3D-Test/Test/Siv3DTest_OSX.cpp"
#	"../../Siv3D-Test/Test/Siv3DTest_Windows.cpp"
)

target_link_libraries(Siv3D_Test
#	-lgtest
#	-lgtest_main
	-lboost_filesystem
	-lboost_system
	-lpthread
	-lGL
	-lGLEW
	-lglib-2.0
	-lgobject-2.0
	-lgio-2.0
	-lpng
	-lturbojpeg
	-lX11
	-lXi
	-lXrandr
	-lXinerama
	-lXcursor
	-ldl
	-lgif
	-lfreetype
	-lharfbuzz
	-lopenal
	
	${PROJECT_SOURCE_DIR}/../Debug/libSiv3D.a
	${PROJECT_SOURCE_DIR}/../../Siv3D/lib/Linux/angelscript/libangelscript.a
)

