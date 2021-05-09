cmake_minimum_required(VERSION 3.12)
project(OpenSiv3D_Linux_App CXX C)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fPIC -msse4.1 -D_GLFW_X11")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -fPIC -msse4.1 -D_GLFW_X11")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options ("-fdiagnostics-color=always")
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(Siv3DTest
  Main.cpp
  ../../Test/Siv3DTest.cpp
  ../../Test/Siv3DTest_Array.cpp
  ../../Test/Siv3DTest_BinaryReader.cpp
  ../../Test/Siv3DTest_BinaryWriter.cpp
  ../../Test/Siv3DTest_FileSystem.cpp
  ../../Test/Siv3DTest_Image.cpp
  ../../Test/Siv3DTest_Resource.cpp
  ../../Test/Siv3DTest_Stopwatch.cpp
  ../../Test/Siv3DTest_TextEncoding.cpp
  ../../Test/Siv3DTest_TextReader.cpp
  ../../Test/Siv3DTest_TextWriter.cpp
  ../../Test/Siv3DTest_Timer.cpp
  )
target_include_directories(Siv3DTest PRIVATE
  "/usr/include"
  "../../Siv3D/include"
  "../../Siv3D/include/ThirdParty"
  )
target_link_libraries(Siv3DTest PRIVATE
  ${PROJECT_SOURCE_DIR}/../build/libSiv3D.a
  -lpthread
  -ldl
  -lGL
  -lX11
  -lfreetype
  -lglib-2.0
  -lgobject-2.0
  -lgif
  -lgio-2.0
  -lharfbuzz
	-logg
  -lopencv_core
  -lopencv_imgcodecs
  -lopencv_imgproc
  -lopencv_objdetect
  -lopencv_photo
  -lopencv_videoio
  -lpng
  -lturbojpeg
	-lvorbis
	-lvorbisenc
	-lvorbisfile
  -lwebp
  )


if(BUILD_TESTING)
enable_testing()
add_test(
  NAME Test
  COMMAND Siv3DTest
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endif()
