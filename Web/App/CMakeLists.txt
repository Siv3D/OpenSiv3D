cmake_minimum_required(VERSION 3.12)
project(OpenSiv3D_Web_App CXX C)

#
# General Options
#
option(CMAKE_PREFIX_PATH "Custom Siv3D installation path" ${EMSCRIPTEN_SYSROOT})
option(CMAKE_FIND_ROOT_PATH "Custom Siv3D installation path" ${EMSCRIPTEN_SYSROOT})

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

#
# Siv3D App Definition
#
add_executable(Siv3DApp
  Main.cpp
)

#
# Pre-bundled Files
#
set(SIV3D_BUNDLED_FILES
    /resources/engine
)

#
# Asyncify Setting
#
set(SIV3D_ASYNCIFY_ADD
  main
  "Main()"
  dynCall_v
  dynCall_vi
  "s3d::TryMain()"
  "s3d::CSystem::init()"
  "s3d::System::Update()"

  "s3d::AACDecoder::decode(*) const"
  "s3d::MP3Decoder::decode(*) const"
  "s3d::CAudioDecoder::decode(*)"
  "s3d::AudioDecoder::Decode(*)"
  "s3d::Wave::Wave(*)"
  "s3d::Audio::Audio(*)"

  "s3d::GenericDecoder::decode(*) const"
  "s3d::CImageDecoder::decode(*)"
  "s3d::Image::Image(*)"
  "s3d::Texture::Texture(*)"
  "s3d::ImageDecoder::Decode(*)"
  "s3d::ImageDecoder::GetImageInfo(*)"

  "s3d::Model::Model(*)"
  "s3d::CModel::create(*)"

  "s3d::CRenderer2D_GLES3::init()"
  "s3d::CRenderer2D_WebGPU::init()"

  "s3d::Clipboard::GetText(*)"
  "s3d::CClipboard::getText(*)"

  "s3d::SimpleHTTP::Save(*)"
  "s3d::SimpleHTTP::Load(*)"
  "s3d::SimpleHTTP::Get(*)"
  "s3d::SimpleHTTP::Post(*)"

  "s3d::VideoReader::VideoReader(*)"
  "s3d::VideoReader::open(*)"

  "s3d::Platform::Web::FetchFile(*)"
)

set(SIV3D_ASYNCIFY_IMPORTS
  siv3dRequestAnimationFrame
  siv3dGetClipboardText
  siv3dDecodeImageFromFile
  siv3dSleepUntilWaked
  invoke_v
  invoke_vi
)



#
# General Options
#
find_package(Siv3D REQUIRED)

set(SIV3D_CXX_DEFINITIONS)
set(SIV3D_EXE_LINKER_FLAGS
  --no-export-dynamic
  -sERROR_ON_UNDEFINED_SYMBOLS=0
  -sALLOW_MEMORY_GROWTH=1
  -sUSE_GLFW=3
  -sUSE_OGG=1
  -sUSE_VORBIS=1
  -sASYNCIFY=1
  -sASYNCIFY_IGNORE_INDIRECT=1
  -sUSE_PTHREADS=1
  -sPROXY_TO_PTHREAD=1
  -sUSE_WEBGPU=1
  -sFULL_ES3
  -sMIN_WEBGL_VERSION=2
  -sMAX_WEBGL_VERSION=2
  --emrun
  -sMODULARIZE=1
  -sEXPORT_NAME=Runtime
  --shell-file=${CMAKE_CURRENT_SOURCE_DIR}/Templates/Embeddable/web-player.html
  --post-js=${CMAKE_CURRENT_SOURCE_DIR}/Templates/Embeddable/web-player.js
)
set(SIV3D_LINK_LIBRARIES
  -Wl,--whole-archive
    Siv3D::Siv3DWebGPU
  -Wl,--no-whole-archive
    Siv3D::Siv3D
    Siv3D::Siv3DScript
)



#
# Helper Functions: target_asyncify_imports, target_asyncify_add, target_exported_functions, target_preload_files
#
function(target_add_listed_link_options target option_name)
  set(option_list ${ARGN})
  list (TRANSFORM option_list REPLACE ".+" "'\\0'")
  string (REPLACE ";" "," option_list "${option_list}")
  target_link_options(${target} PRIVATE -s${option_name}=[${option_list}])
endfunction()

function(target_asyncify_imports target)
  target_add_listed_link_options(${target} "ASYNCIFY_IMPORTS" ${ARGN})
endfunction()

function(target_asyncify_add target)
  target_add_listed_link_options(${target} "ASYNCIFY_ADD" ${ARGN})
endfunction()

function(target_exported_functions target)
  target_add_listed_link_options(${target} "EXPORTED_FUNCTIONS" ${ARGN})
endfunction()

function(target_preload_files target)
  set(SIV3D_BUNDLED_FILES_LINKER_FLAGS "")

  foreach(file ${SIV3D_BUNDLED_FILES})
      list(APPEND SIV3D_BUNDLED_FILES_LINKER_FLAGS "--preload-file=${CMAKE_CURRENT_SOURCE_DIR}${file}@${file}")
  endforeach()

  target_link_options(${target} PRIVATE ${SIV3D_BUNDLED_FILES_LINKER_FLAGS})
endfunction()



#
# Siv3D App Definition
#
target_compile_definitions(Siv3DApp PRIVATE ${SIV3D_CXX_DEFINITIONS})
target_compile_features(Siv3DApp PRIVATE cxx_std_20)
target_link_options(Siv3DApp PRIVATE ${SIV3D_EXE_LINKER_FLAGS})
target_link_libraries(Siv3DApp PRIVATE ${SIV3D_LINK_LIBRARIES})

set_target_properties(Siv3DApp PROPERTIES
    SUFFIX ".html"
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

target_asyncify_imports(Siv3DApp ${SIV3D_ASYNCIFY_IMPORTS})
target_asyncify_add(Siv3DApp ${SIV3D_ASYNCIFY_ADD})
target_preload_files(Siv3DApp ${SIV3D_BUNDLED_FILES})
