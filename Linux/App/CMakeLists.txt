cmake_minimum_required(VERSION 3.12)
project(OpenSiv3D_Linux_App CXX)

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(Siv3DTest
  Main.cpp
  #../../Test/Siv3DTest.cpp
  #../../Test/Siv3DTest_Array.cpp
  #../../Test/Siv3DTest_BinaryReader.cpp
  #../../Test/Siv3DTest_BinaryWriter.cpp
  #../../Test/Siv3DTest_FileSystem.cpp
  #../../Test/Siv3DTest_Image.cpp
  #../../Test/Siv3DTest_Resource.cpp
  #../../Test/Siv3DTest_Stopwatch.cpp
  #../../Test/Siv3DTest_TextEncoding.cpp
  #../../Test/Siv3DTest_TextReader.cpp
  #../../Test/Siv3DTest_TextWriter.cpp
  #../../Test/Siv3DTest_Timer.cpp
  )

find_package(Siv3D)
target_link_libraries(Siv3DTest PUBLIC Siv3D::Siv3D)

target_compile_features(Siv3DTest PRIVATE cxx_std_20)

if(BUILD_TESTING)
enable_testing()
add_test(
  NAME Test
  COMMAND Siv3DTest
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endif()
