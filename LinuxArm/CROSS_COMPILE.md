# How to cross-compile for ARM (aarch64) on x86_64
This document assumes you are working on Ubuntu 20.04.

## Prerequisites
- [Software needed to build Siv3D for x86_64](https://github.com/Siv3D/OpenSiv3D/blob/main/.github/workflows/ci.yml#L26-L49)
- `qemu-user-static`, `mmdebstrap`, `g++-aarch64-linux-gnu`

## Build procedure
1. Use `mmdebstrap` to prepare directory tree of Ubuntu ARM inside `~/ubuntu-arm64`
```sh
mmdebstrap --arch=arm64 --components="main universe" --include="ninja-build,libasound2-dev,libavcodec-dev,libavformat-dev,libavutil-dev,libboost-dev,libcurl4-openssl-dev,libgtk-3-dev,libgif-dev,libglu1-mesa-dev,libharfbuzz-dev,libmpg123-dev,libopencv-dev,libopus-dev,libopusfile-dev,libsoundtouch-dev,libswresample-dev,libtiff-dev,libturbojpeg0-dev,libvorbis-dev,libwebp-dev,libxft-dev,uuid-dev,xorg-dev" focal ~/ubuntu-arm64 http://jp.archive.ubuntu.com/ports/
```
2. Build Siv3D library
```sh
cd OpenSiv3D/LinuxArm/
mkdir build
cd build/
cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../aarch64-cross.cmake ..
cmake --build .
```
3. Build the example application
```sh
cd ../App/
mkdir build
cd build/
cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../../aarch64-cross.cmake ..
cmake --build .
```
