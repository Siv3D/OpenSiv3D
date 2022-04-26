#!/bin/bash

RepositoryName="EmscriptenLibraries"
RepositoryAddress="https://github.com/nokotan/EmscriptenLibraries.git"
RepositoryLicense="MIT License"

function init() {
    if [ ! -e "${RepositoryName}" ]; then
        git clone ${RepositoryAddress} --depth 1
    fi

    cd ${RepositoryName}
}

function build() {
    while [ "${1}" != "" ]; do
    case "${1}" in
        zlib)
            ./emlib.sh build zlib
            cp lib/libz.a       ../../../Siv3D/lib/Web/wasm/zlib/;;
        png)
            ./emlib.sh build libpng
            cp lib/libpng.a     ../../../Siv3D/lib/Web/wasm/png/;;
        freetype)
            ./emlib.sh build freetype
            cp lib/libfreetype.a ../../../Siv3D/lib/Web/wasm/freetype/;;
        giflib)
            ./emlib.sh build giflib
            cp lib/libgif.a     ../../../Siv3D/lib/Web/wasm/giflib/;;
        opencv)
            ./emlib.sh build opencv
            cp lib/libopencv_core.a         ../../../Siv3D/lib/Web/wasm/opencv/
            cp lib/libopencv_imgproc.a      ../../../Siv3D/lib/Web/wasm/opencv/
            cp lib/libopencv_objdetect.a    ../../../Siv3D/lib/Web/wasm/opencv/
            cp lib/libopencv_photo.a        ../../../Siv3D/lib/Web/wasm/opencv/;;
        giflib)
            ./emlib.sh build giflib
            cp lib/libgif.a     ../../../Siv3D/lib/Web/wasm/giflib/;;
        opus)
            ./emlib.sh build opus opusfile
            cp lib/libopus.a        ../../../Siv3D/lib/Web/wasm/opus/
            cp lib/libopusfile.a    ../../../Siv3D/lib/Web/wasm/opus/;;
        tiff)
            ./emlib.sh build tiff
            cp lib/libtiff.a    ../../../Siv3D/lib/Web/wasm/tiff/;;
        turbojpeg)
            ./emlib.sh build turbojpeg
            cp lib/turbojpeg.a  ../../../Siv3D/lib/Web/wasm/turbojpeg/;;
        webp)
            ./emlib.sh build webp
            cp lib/libwebp.a    ../../../Siv3D/lib/Web/wasm/webp/;;
        SDL2)
            echo "Now Preparing... Skip.";;
        *)
            echo "Not recognized library name: ${1}... Skip.";;
    esac
    shift 1
    done
}

function build_all() {
    local libs=(
        "zlib"
        "png"
        "freetype"
        "giflib"
        "opencv"
        "opus"
        "tiff"
        "turbojpeg"
        "webp"
    )

    for elem in ${libs[@]}; do
        build $elem
    done
}

init
build_all
