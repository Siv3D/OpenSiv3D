cmake_minimum_required(VERSION 2.8)

project(open_siv3d_linux_test CXX)

set(CMAKE_CXX_COMPILER "clang++")
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")

#set(CMAKE_BUILD_TYPE Release)

#add_definitions(-D)

include_directories(
	"/usr/include"
	"../../Siv3D-Test/Include"
	"../../Siv3D/Include"
)

link_directories(
	"/usr/lib"
	"../Debug"
)

add_executable(siv3d_test
	"../../Siv3D-Test/Main.cpp"

	"../../Siv3D-Test/Test/Siv3DTest.hpp"
	"../../Siv3D-Test/Test/TestAlignedMemory.cpp"
	"../../Siv3D-Test/Test/TestArray.cpp"
	"../../Siv3D-Test/Test/TestBase64.cpp"
	"../../Siv3D-Test/Test/TestCharacterSet.cpp"
	"../../Siv3D-Test/Test/TestConcept.cpp"
	"../../Siv3D-Test/Test/TestFileSystem.cpp"
	"../../Siv3D-Test/Test/TestFormatBool.cpp"
	"../../Siv3D-Test/Test/TestFormatFloat.cpp"
	"../../Siv3D-Test/Test/TestFormatInt.cpp"
	"../../Siv3D-Test/Test/TestMath.cpp"
	"../../Siv3D-Test/Test/TestNamedParameter.cpp"
	"../../Siv3D-Test/Test/TestOptional.cpp"
	"../../Siv3D-Test/Test/TestStep.cpp"
	"../../Siv3D-Test/Test/TestString.cpp"
	"../../Siv3D-Test/Test/TestTypes.cpp"
	"../../Siv3D-Test/Test/TestUtility.cpp"

	"../../Siv3D-Test/Test/Siv3DTest_Linux.cpp"

#	"../../Siv3D-Test/Test/Siv3DTest_OSX.cpp"
#	"../../Siv3D-Test/Test/Siv3DTest_Windows.cpp"
)

target_link_libraries(siv3d_test
	gtest
	gtest_main
	siv3d
	boost_filesystem
	boost_system
	pthread
	glfw
	GL
	glib-2.0
	gobject-2.0
	gio-2.0
	png
	turbojpeg
)

