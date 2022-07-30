cmake_minimum_required(VERSION 3.12)

project(OpenSiv3D_Web_App CXX C)

#
# General Options
#

option(SIV3D_ENABLE_SHARED_LIB "Enable WebAssembly shared library linking. (emscripten's experimental feature)" OFF)
option(SIV3D_BUILD_WITH_SHARED_MAIN "Build plugin-style Siv3D application loader." OFF)
option(SIV3D_BUILD_TESTING "Build tests and run." OFF)
option(SIV3D_WEBGPU_BACKEND "Enable WebGPU rendering backend." OFF)

# Siv3D is supposed to be installed to emscripten sysroot folder.
# Use `make install` when building Siv3d manually.
if (NOT CMAKE_PREFIX_PATH)
  set(CMAKE_PREFIX_PATH ${EMSCRIPTEN_SYSROOT})
endif ()

find_package(OpenSiv3D REQUIRED)
find_package(OpenSiv3DScript)
find_package(OpenSiv3DWebGPU)
find_package(OpenSiv3DBrowserImageEncodeDecode)


#
# General Compile Options
#

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

#
# General Linker Options
#

set(Siv3DLinkerFlags
  --no-export-dynamic
  -s ERROR_ON_UNDEFINED_SYMBOLS=0
  -s ALLOW_MEMORY_GROWTH=1
  -s USE_GLFW=3
  -s USE_OGG=1
  -s USE_VORBIS=1
  --js-library ${CMAKE_PREFIX_PATH}/lib/Siv3D/Siv3D.js
  --pre-js ${CMAKE_PREFIX_PATH}/lib/Siv3D/Siv3D.pre.js
)

string(REPLACE ";" " " Siv3DLinkerFlags "${Siv3DLinkerFlags}")
add_link_options("SHELL:${Siv3DLinkerFlags}")

#
# Configuration-specific Additional Flags
#

# Use DirectXMath no-simd version when WebAssembly simd is disabled 
if (NOT ${CMAKE_C_FLAGS} MATCHES "-msimd128" OR NOT ${CMAKE_CXX_FLAGS} MATCHES "-msimd128")
  add_compile_options ("-D_XM_NO_INTRINSICS_")
endif ()

# Use exception handling when configuration is not MINSIZEREL
if (NOT CMAKE_BUILD_TYPE STREQUAL "MINSIZEREL")
  add_compile_options ("SHELL:-s EXCEPTION_CATCHING_ALLOWED=[\"InitSiv3D\"]")
  add_link_options ("SHELL:-s EXCEPTION_CATCHING_ALLOWED=[\"InitSiv3D\"]")
endif()

if (SIV3D_WEBGPU_BACKEND)
  add_compile_options("-DSIV3D_WEBGPU_BACKEND")
  add_link_options(
    "SHELL:-s USE_WEBGPU=1"
    "SHELL:--post-js \"${CMAKE_PREFIX_PATH}/lib/Siv3D/Siv3D.post.js\""
  )
else()
  add_link_options(
    "SHELL:-s FULL_ES3"
    "SHELL:-s MIN_WEBGL_VERSION=2"
    "SHELL:-s MAX_WEBGL_VERSION=2"
  )
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options ("-fdiagnostics-color=always")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})



#
# Siv3D App Definition
#

add_executable(Siv3DApp
  Main.cpp
)

target_include_directories(Siv3DApp 
  PRIVATE
    OpenSiv3D
)

target_link_libraries(Siv3DApp
  PRIVATE
    # "-Wl,--whole-archive"
    #   OpenSiv3DBrowserImageEncodeDecode
    "-Wl,--no-whole-archive"
      OpenSiv3D
      # OpenSiv3DWebGPU
      # OpenSiv3DScript
)

set(Siv3DLinkerFlags
  -s MODULARIZE=1
  -s ASYNCIFY=1
  -s ASYNCIFY_IGNORE_INDIRECT=1
  --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/Templates/Embeddable/web-player.html
  --post-js ${CMAKE_CURRENT_SOURCE_DIR}/Templates/Embeddable/web-player.js
)

set_target_properties(Siv3DApp
  PROPERTIES
    SUFFIX ".html"
)

#
# Packaged Files
#
set(Siv3DAppBundledFilesPath
    /resources/engine/font/min/siv3d-min.woff
    /resources/engine/font/noto-emoji/LICENSE
    /resources/engine/font/noto-emoji/NotoEmoji-Regular.ttf.zstdcmp
    /resources/engine/shader/essl
    /resources/engine/shader/wgsl
    /resources/engine/texture/box-shadow
    /resources/engine/font/noto-cjk/NotoSansCJK-Regular.ttc.zstdcmp
    /resources/engine/font/noto-emoji/NotoColorEmoji.ttf.zstdcmp
    /resources/engine/font/mplus/mplus-1p-regular.ttf.zstdcmp
    /example/windmill.png
)

set(Siv3DAppBundledFilesFlags "")

foreach(file ${Siv3DAppBundledFilesPath})
    list(APPEND Siv3DLinkerFlags "--preload-file")
    list(APPEND Siv3DLinkerFlags "${CMAKE_CURRENT_SOURCE_DIR}${file}@${file}")
endforeach()

#
# Asyncify Setting
#
if (SIV3D_BUILD_WITH_SHARED_MAIN)

  set(ASYNCIFY_IMPORTS _ZN3s3d6System6UpdateEv)
  set(ASYNCIFY_ADD "Main()")

else ()

  set(ASYNCIFY_IMPORTS
    "siv3dRequestAnimationFrame"
    "siv3dOpenDialog"
    "siv3dDecodeAudioFromFile"
    "siv3dGetClipboardText"
    "siv3dDecodeImageFromFile"
  )

  set(ASYNCIFY_ADD
    "main"
    "Main()"
    "InitSiv3D"
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
    "s3d::CRenderer2D_GLES3::init()"
    "s3d::CRenderer2D_WebGPU::init()"
    "s3d::Clipboard::GetText(*)"
    "s3d::CClipboard::getText(*)"
  )
endif ()

list (TRANSFORM ASYNCIFY_IMPORTS REPLACE ".+" "'\\0'")
list (TRANSFORM ASYNCIFY_ADD REPLACE ".+" "'\\0'")
string (REPLACE ";" "," ASYNCIFY_IMPORTS "${ASYNCIFY_IMPORTS}")
string (REPLACE ";" "," ASYNCIFY_ADD "${ASYNCIFY_ADD}")

list (APPEND Siv3DLinkerFlags
  "-s ASYNCIFY_IMPORTS=\"[${ASYNCIFY_IMPORTS}]\""
  "-s ASYNCIFY_ADD=\"[${ASYNCIFY_ADD}]\""
)
string(REPLACE ";" " " Siv3DLinkerFlags "${Siv3DLinkerFlags}")
target_link_options(Siv3DApp
  PRIVATE
    "SHELL:${Siv3DLinkerFlags}"
)

#
# Dynamic Linking Flags
#
if (SIV3D_ENABLE_SHARED_LIB)

  set(EXPORTED_FUNCTIONS
    "___THREW__, ___threwValue, _saveSetjmp, _stderr, _stdout, _stdin, 
    _main, _memset, _memcpy, _memmove, _memcmp, _realloc, _calloc, _strcmp, _strlen, _strncpy, _strtoul,
    _strtol, _strncmp, _strstr, _strchr, _strncmp, _getenv, _open, _fopen, _fclose, _fseek, _fread, _ftell, _fstat,
    _pthread_mutex_init, _pthread_mutex_lock, _pthread_mutex_unlock, _sysconf, ___errno_location, _strerror,
    _mprotect, _mmap, _munmap, _setlocale")

  string(REPLACE "\n" " " EXPORTED_FUNCTIONS ${EXPORTED_FUNCTIONS})
  target_link_options(Siv3DApp PRIVATE "SHELL:-s EXPORTED_FUNCTIONS=\"[${EXPORTED_FUNCTIONS}]\"")

  target_compile_options(Siv3DApp
    PRIVATE
      "SHELL:-s MAIN_MODULE=2"
  )

  target_link_options(Siv3DApp
    PRIVATE
      "SHELL:-s MAIN_MODULE=2"
  )

elseif (SIV3D_BUILD_WITH_SHARED_MAIN)

  target_compile_options(Siv3DApp
    PRIVATE
      "SHELL:-s SIDE_MODULE=1"
  )

  set_target_properties(Siv3DApp
    PROPERTIES
      SUFFIX ".wasm"
  )

endif()



#
# Siv3D DinamicLink EntryPoint App
#

add_executable(Siv3DSharedMain 
  EXCLUDE_FROM_ALL
  Empty.cpp
)

if (SIV3D_BUILD_WITH_SHARED_MAIN)
  set_target_properties(Siv3DSharedMain 
    PROPERTIES
      EXCLUDE_FROM_ALL On
  )
endif()

target_compile_options(Siv3DSharedMain PRIVATE
  "-sMAIN_MODULE=1"
  "-DZSTD_TRACE=0"
)

set(Siv3DSharedMainLinkerOption
  "-s MAIN_MODULE=1"
  "-s DECLARE_ASM_MODULE_EXPORTS=0"
  "-s EXPORTED_FUNCTIONS='[\"_main\"]'"

  "--pre-js 'Siv3D.data.js'"
  "-s FORCE_FILESYSTEM=1"

  # "-s ASYNCIFY=1"
  # "-s ASYNCIFY_IGNORE_INDIRECT=1"
)

set(ASYNCIFY_IMPORTS
  "siv3dRequestAnimationFrame"
  "siv3dOpenDialog"
  "siv3dDecodeAudioFromFile"
  "siv3dGetClipboardText"
  "_Z4Mainv"
)

set(ASYNCIFY_ADD
  "main"
  "InitSiv3D"
  "s3d::CSystem::init()"
  "s3d::System::Update()"
  "s3d::AACDecoder::decode(*) const"
  "s3d::MP3Decoder::decode(*) const"
  "s3d::CAudioDecoder::decode(*)"
  "s3d::AudioDecoder::Decode(*)"
  "s3d::Wave::Wave(*)"
  "s3d::Audio::Audio(*)"
  "s3d::Clipboard::GetText(*)"
  "s3d::CClipboard::getText(*)"
)

set_target_properties(Siv3DSharedMain 
  PROPERTIES
    SUFFIX ".html"
)

target_include_directories(Siv3DSharedMain 
  PRIVATE
    OpenSiv3D
)

target_link_libraries(Siv3DSharedMain
  PRIVATE
    OpenSiv3D
)

add_custom_command(
  OUTPUT Siv3D.data Siv3D.data.js
  COMMAND python3 
  ARGS
    $ENV{EMSDK}/upstream/emscripten/tools/file_packager.py
    Siv3D.data
    --js-output=Siv3D.data.js
    --preload \"${CMAKE_SOURCE_DIR}/App/resources@/resources\"
    --from-emcc
)

add_custom_target(Siv3DAppData
  DEPENDS
    Siv3D.data Siv3D.data.js
)

add_dependencies(Siv3DSharedMain
  Siv3DAppData
)

list (TRANSFORM ASYNCIFY_IMPORTS REPLACE ".+" "'\\0'")
list (TRANSFORM ASYNCIFY_ADD REPLACE ".+" "'\\0'")
string (REPLACE ";" "," ASYNCIFY_IMPORTS "${ASYNCIFY_IMPORTS}")
string (REPLACE ";" "," ASYNCIFY_ADD "${ASYNCIFY_ADD}")

# list (APPEND Siv3DSharedMainLinkerOption
#   "-s ASYNCIFY_IMPORTS=\"[${ASYNCIFY_IMPORTS}]\""
#   "-s ASYNCIFY_ADD=\"[${ASYNCIFY_ADD}]\""
# )
string (REPLACE ";" " " Siv3DSharedMainLinkerOption "${Siv3DSharedMainLinkerOption}")

target_link_options(Siv3DSharedMain PRIVATE
  "SHELL:${Siv3DSharedMainLinkerOption}"
)



#
# Test Definition
#

add_executable(Siv3DTest
  EXCLUDE_FROM_ALL
  TestMain.cpp
  ../../Test/Siv3DTest.cpp
  ../../Test/Siv3DTest_Array.cpp
  ../../Test/Siv3DTest_BinaryReader.cpp
  ../../Test/Siv3DTest_BinaryWriter.cpp
  # ../../Test/Siv3DTest_FileSystem.cpp
  ../../Test/Siv3DTest_Image.cpp
  ../../Test/Siv3DTest_Resource.cpp
  ../../Test/Siv3DTest_TextEncoding.cpp
  ../../Test/Siv3DTest_TextReader.cpp
  ../../Test/Siv3DTest_TextWriter.cpp
)

target_include_directories(Siv3DTest
  PRIVATE
    OpenSiv3D
)

target_link_libraries(Siv3DTest
  PRIVATE
    OpenSiv3D
)

target_link_options(Siv3DTest
  PRIVATE
    "-lnodefs.js"
    "SHELL:--pre-js \"${CMAKE_SOURCE_DIR}/../../Test/Siv3DTest.js\""
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
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endif()
