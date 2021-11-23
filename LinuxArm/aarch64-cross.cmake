# クロスコンパイル用の設定
# 参考：https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-linux

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_SYSROOT /home/tana/ubuntu-arm64)  # 自分の環境に合わせて変える

set(triple aarch64-linux-gnu)
set(CMAKE_C_COMPILER ${triple}-gcc)
set(CMAKE_CXX_COMPILER ${triple}-g++)
#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_C_COMPILER_TARGET ${triple})
#set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# To fix link error related to BLAS and LAPACK
add_link_options(-Wl,-rpath-link=${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/blas -Wl,-rpath-link=${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/lapack)

# pkg-configがaarch64用のライブラリを検索するように設定
# 参考：https://stackoverflow.com/questions/9221236/pkg-config-fails-to-find-package-under-sysroot-directory
set(ENV{PKG_CONFIG_DIR} "")
set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig:${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig)
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
