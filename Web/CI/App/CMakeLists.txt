cmake_minimum_required(VERSION 3.12)
project(OpenSiv3D_Web_App CXX C ASM)

#
# General Options
#
option(SIV3D_WEBGPU_BACKEND "Enable WebGPU rendering backend." OFF)
option(SIV3D_USE_SCRIPT "Enable Siv3D Script." OFF)
option(SIV3D_USE_ASYNCIFY "Enable synchronous operations with emscripten's Asyncify." ON)
option(SIV3D_USE_PROXY_TO_PTHREAD "Enable synchronous operations with emscripten's PROXY_TO_PTHREAD." OFF)
option(SIV3D_USE_BROWSER_IMAGE_ENCODING "Enable Browser Image Encoding." OFF)

option(SIV3D_ENABLE_SHARED_LIB "Enable WebAssembly shared library linking. (emscripten's experimental feature)" OFF)
option(SIV3D_BUILD_WITH_SHARED_MAIN "Build plugin-style Siv3D application loader." OFF)
option(SIV3D_BUILD_TESTING "Build tests and run." OFF)

set(SIV3D_APP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../App)

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
    /resources/engine/font/min/siv3d-min.woff
    /resources/engine/font/noto-emoji/LICENSE
    /resources/engine/font/noto-emoji/NotoEmoji-Regular.ttf.zstdcmp
    /resources/engine/shader/essl
    /resources/engine/shader/wgsl
    /resources/engine/texture/box-shadow
    /resources/engine/font/noto-cjk/NotoSansCJK-Regular.ttc.zstdcmp
    /resources/engine/font/noto-emoji/NotoColorEmoji.ttf.zstdcmp
    /resources/engine/font/mplus/mplus-1p-regular.ttf.zstdcmp
)

#
# Asyncify Setting
#
set(SIV3D_ASYNCIFY_IMPORTS
  siv3dRequestAnimationFrame
  siv3dGetClipboardText
  siv3dDecodeImageFromFile
  siv3dSleepUntilWaked
  invoke_v
  invoke_vi
)

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



#
# General Options
#
find_package(Siv3D REQUIRED)

set(SIV3D_CXX_DEFINITIONS)
set(SIV3D_CXX_FLAGS)
set(SIV3D_EXE_LINKER_FLAGS
  --no-export-dynamic
  -sERROR_ON_UNDEFINED_SYMBOLS=0
  -sALLOW_MEMORY_GROWTH=1
  -sUSE_GLFW=3
  -sUSE_OGG=1
  -sUSE_VORBIS=1  
)
set(SIV3D_LINK_LIBRARIES
  Siv3D::Siv3D
)
set(SIV3DAPP_EXE_LINKER_FLAGS
  -sEXIT_RUNTIME=1
  --shell-file=${CMAKE_SOURCE_DIR}/CIAppShell.html
)



#
# Configuration-specific Flags
#
if (SIV3D_USE_ASYNCIFY)
  list(APPEND SIV3D_EXE_LINKER_FLAGS
    -sASYNCIFY=1
    -sASYNCIFY_IGNORE_INDIRECT=1
  )
endif()

if (SIV3D_USE_PROXY_TO_PTHREAD)
  list(APPEND SIV3D_CXX_FLAGS
    -sUSE_PTHREAD=1
  )
  list(APPEND SIV3D_EXE_LINKER_FLAGS
    -sUSE_PTHREAD=1
    -sPROXY_TO_PTHREAD=1
  )
endif()

if (SIV3D_WEBGPU_BACKEND)
  list(APPEND SIV3D_CXX_DEFINITIONS
    SIV3D_WEBGPU_BACKEND
  )
  list(APPEND SIV3D_EXE_LINKER_FLAGS
    -sUSE_WEBGPU=1
  )
  list(PREPEND SIV3D_LINK_LIBRARIES
    -Wl,--whole-archive
      Siv3D::Siv3DWebGPU
    -Wl,--no-whole-archive
  )
else()
  list(APPEND SIV3D_EXE_LINKER_FLAGS
    -sFULL_ES3
    -sMIN_WEBGL_VERSION=2
    -sMAX_WEBGL_VERSION=2
  )
endif()

if (SIV3D_USE_BROWSER_IMAGE_ENCODING)
  list(PREPEND SIV3D_LINK_LIBRARIES
    -Wl,--whole-archive
      Siv3D::Siv3DBrowserImageEncodeDecode
    -Wl,--no-whole-archive
  )
endif()

if (SIV3D_USE_SCRIPT)
  list(APPEND SIV3D_LINK_LIBRARIES
    Siv3D::Siv3DScript
  )
endif()



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
      list(APPEND SIV3D_BUNDLED_FILES_LINKER_FLAGS "--preload-file=${SIV3D_APP_ROOT}${file}@${file}")
  endforeach()

  target_link_options(${target} PRIVATE ${SIV3D_BUNDLED_FILES_LINKER_FLAGS})
endfunction()



#
# Siv3DApp Common Option Target
#
add_library(Siv3DAppInterface INTERFACE)

target_compile_definitions(Siv3DAppInterface INTERFACE ${SIV3D_CXX_DEFINITIONS})
target_compile_options(Siv3DAppInterface INTERFACE ${SIV3D_CXX_FLAGS})
target_link_options(Siv3DAppInterface INTERFACE ${SIV3D_EXE_LINKER_FLAGS} ${SIV3DAPP_EXE_LINKER_FLAGS})
target_link_libraries(Siv3DAppInterface INTERFACE ${SIV3D_LINK_LIBRARIES})

add_library(Siv3DInterface INTERFACE)

target_compile_definitions(Siv3DInterface INTERFACE ${SIV3D_CXX_DEFINITIONS})
target_link_options(Siv3DInterface INTERFACE ${SIV3D_EXE_LINKER_FLAGS})
target_link_libraries(Siv3DInterface INTERFACE ${SIV3D_LINK_LIBRARIES})



#
# Siv3D App Definition
#
if (SIV3D_BUILD_WITH_SHARED_MAIN)
  set_target_properties(Siv3DApp PROPERTIES
      EXCLUDE_FROM_ALL On
  )
endif()

target_link_libraries(Siv3DApp PRIVATE Siv3DAppInterface)
target_compile_features(Siv3DApp PRIVATE cxx_std_20)
set_target_properties(Siv3DApp PROPERTIES
    SUFFIX .html
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

target_asyncify_imports(Siv3DApp ${SIV3D_ASYNCIFY_IMPORTS})
target_asyncify_add(Siv3DApp ${SIV3D_ASYNCIFY_ADD})
target_preload_files(Siv3DApp ${SIV3D_BUNDLED_FILES})



#
# Siv3D Shared Library App
#
add_executable(Siv3DSharedLibApp
  EXCLUDE_FROM_ALL
  Main.cpp
)

set(SIV3D_SHAREDLIB_EXPORTED_FUNCTIONS
  ___THREW__ ___threwValue _saveSetjmp _stderr _stdout _stdin
  _main _memset _memcpy _memmove _memcmp _realloc _calloc _strcmp _strlen _strncpy _strtoul
  _strtol _strncmp _strstr _strchr _strncmp _getenv _open _fopen _fclose _fseek _fread _ftell _fstat
  _pthread_mutex_init _pthread_mutex_lock _pthread_mutex_unlock _sysconf ___errno_location _strerror
  _mprotect _mmap _munmap _setlocale)

target_link_libraries(Siv3DSharedLibApp PRIVATE Siv3DAppInterface)
target_compile_features(Siv3DSharedLibApp PRIVATE cxx_std_20) 
target_compile_options(Siv3DSharedLibApp PRIVATE -sMAIN_MODULE=2)
target_link_options(Siv3DSharedLibApp PRIVATE -sMAIN_MODULE=2)
set_target_properties(Siv3DSharedLibApp PROPERTIES
    SUFFIX .html
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

target_exported_functions(Siv3DSharedLibApp SIV3D_SHAREDLIB_EXPORTED_FUNCTIONS)
target_asyncify_imports(Siv3DSharedLibApp ${SIV3D_ASYNCIFY_IMPORTS})
target_asyncify_add(Siv3DSharedLibApp ${SIV3D_ASYNCIFY_ADD})
target_preload_files(Siv3DSharedLibApp ${SIV3D_BUNDLED_FILES})



#
# Siv3D DinamicLink App
#
add_executable(Siv3DSharedMainApp
  EXCLUDE_FROM_ALL
  Main.cpp
)

set(SIV3D_SHAREDMAIN_APP_ASYNCIFY_IMPORTS 
  _ZN3s3d6System6UpdateEv
  _ZN3s3d7TextureC1ENS_10StringViewENS_11TextureDescE
  _ZN3s3d5ImageC1ENS_10StringViewENS_11ImageFormatE
  _ZN3s3d5AudioC1ENS_10StringViewE
  _ZN3s3d5AudioC1ENS_10StringViewENS_5YesNoINS_8Loop_tagEEE
  _ZN3s3d5ModelC1ENS_10StringViewENS_11ColorOptionE
)
set(SIV3D_SHAREDMAIN_APP_ASYNCIFY_ADD "Main()")

get_target_property(Siv3DIncludeDirectory Siv3D::Siv3D INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(Siv3DCompilerOptions Siv3D::Siv3DInterface INTERFACE_COMPILE_OPTIONS)
get_target_property(Siv3DCompilerDefinitions Siv3D::Siv3DInterface INTERFACE_COMPILE_DEFINITIONS)
get_target_property(Siv3DLinkerOptions Siv3D::Siv3DInterface INTERFACE_LINK_OPTIONS)

target_include_directories(Siv3DSharedMainApp PRIVATE ${Siv3DIncludeDirectory})
target_compile_definitions(Siv3DSharedMainApp PRIVATE ${Siv3DCompilerDefinitions} ${SIV3D_CXX_DEFINITIONS})
target_compile_features(Siv3DSharedMainApp PRIVATE cxx_std_20) 
target_compile_options(Siv3DSharedMainApp PRIVATE ${Siv3DCompilerOptions} -sSIDE_MODULE=2)
target_link_options(Siv3DSharedMainApp PRIVATE ${Siv3DLinkerOptions} ${SIV3D_EXE_LINKER_FLAGS} -sSIDE_MODULE=2)
set_target_properties(Siv3DSharedMainApp PROPERTIES
    SUFFIX .wasm
    OUTPUT_NAME Siv3DApp
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

target_asyncify_imports(Siv3DSharedMainApp ${SIV3D_SHAREDMAIN_APP_ASYNCIFY_IMPORTS})
target_asyncify_add(Siv3DSharedMainApp ${SIV3D_SHAREDMAIN_APP_ASYNCIFY_ADD})
target_exported_functions(Siv3DSharedMainApp __Z4Mainv)



#
# Siv3D DinamicLink EntryPoint App
#
add_executable(Siv3DSharedMain 
  EXCLUDE_FROM_ALL
  Empty.cpp
  DynCallStub.S
)

if (SIV3D_BUILD_WITH_SHARED_MAIN)
  set_target_properties(Siv3DSharedMain Siv3DSharedMainApp
    PROPERTIES
      EXCLUDE_FROM_ALL Off
  )
endif()

get_filename_component(SIV3D_JSLIBRARY_PATH ${Siv3D_DIR} DIRECTORY)
get_filename_component(SIV3D_JSLIBRARY_PATH ${SIV3D_JSLIBRARY_PATH} DIRECTORY)
get_filename_component(SIV3D_JSLIBRARY_PATH ${SIV3D_JSLIBRARY_PATH} DIRECTORY)

set(SIV3D_SHAREDMAIN_APP_LINKER_OPTIONS
  -sEXIT_RUNTIME=1
  -sMAIN_MODULE=1
  -sDECLARE_ASM_MODULE_EXPORTS=0
  -sFORCE_FILESYSTEM=1
  -sASSERTIONS=1
  --pre-js=${SIV3D_JSLIBRARY_PATH}/lib/Siv3D/Siv3D.sharedMain.pre.js
  --pre-js=${CMAKE_SOURCE_DIR}/Siv3D.data.js
  --shell-file=${CMAKE_SOURCE_DIR}/CIAppShell.html
)

set(SIV3D_SHAREDMAIN_ASYNCIFY_IMPORTS
  ${SIV3D_ASYNCIFY_IMPORTS}
  _Z4Mainv
)

set(SIV3D_SHAREDMAIN_ASYNCIFY_ADD
  ${SIV3D_ASYNCIFY_ADD}
  __synccall
  fakeDynCall_v
)

target_link_libraries(Siv3DSharedMain PRIVATE Siv3DInterface)
target_compile_options(Siv3DSharedMain PRIVATE -sMAIN_MODULE=1)
target_compile_definitions(Siv3DSharedMain PRIVATE ZSTD_TRACE=0)
target_compile_features(Siv3DSharedMain PRIVATE cxx_std_20) 
target_link_options(Siv3DSharedMain PRIVATE 
  ${SIV3D_SHAREDMAIN_APP_LINKER_OPTIONS}
)
set_target_properties(Siv3DSharedMain 
  PROPERTIES
    SUFFIX .html
    OUTPUT_NAME Siv3D
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

target_asyncify_imports(Siv3DSharedMain ${SIV3D_SHAREDMAIN_ASYNCIFY_IMPORTS})
target_asyncify_add(Siv3DSharedMain ${SIV3D_SHAREDMAIN_ASYNCIFY_ADD})



#
# Siv3D DinamicLink EntryPoint AppData 
#
add_custom_command(
  OUTPUT Siv3D.data Siv3D.data.js
  COMMAND python3 
  ARGS
    $ENV{EMSDK}/upstream/emscripten/tools/file_packager.py
    "${CMAKE_SOURCE_DIR}/Siv3D.data"
    --js-output="${CMAKE_SOURCE_DIR}/Siv3D.data.js"
    --preload \"${SIV3D_APP_ROOT}/resources@/resources\"
    --from-emcc
)

add_custom_target(Siv3DAppData
  DEPENDS
    Siv3D.data Siv3D.data.js
)

add_dependencies(Siv3DSharedMain
  Siv3DAppData
)



#
# Test Definition
#
add_executable(Siv3DTest
  EXCLUDE_FROM_ALL
  TestMain.cpp
  ../../../Test/Siv3DTest.cpp
  ../../../Test/Siv3DTest_Array.cpp
  ../../../Test/Siv3DTest_BinaryReader.cpp
  ../../../Test/Siv3DTest_BinaryWriter.cpp
  # ../../../Test/Siv3DTest_FileSystem.cpp
  ../../../Test/Siv3DTest_Image.cpp
  ../../../Test/Siv3DTest_Resource.cpp
  ../../../Test/Siv3DTest_TextEncoding.cpp
  ../../../Test/Siv3DTest_TextReader.cpp
  ../../../Test/Siv3DTest_TextWriter.cpp
)

target_link_libraries(Siv3DTest PRIVATE Siv3DInterface)
target_link_options(Siv3DTest PRIVATE 
  -lnodefs.js
  --pre-js=${CMAKE_SOURCE_DIR}/../../../Test/Siv3DTest.js
)
set_target_properties(Siv3DTest
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

if(SIV3D_BUILD_TESTING)
  enable_testing()

  set_target_properties(Siv3DTest
    PROPERTIES
      EXCLUDE_FROM_ALL OFF
  )

  add_test(
    NAME Test
    COMMAND node Siv3DTest.js
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()
