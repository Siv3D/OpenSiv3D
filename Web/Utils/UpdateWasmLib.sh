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
    local targetOption="${1}"
    local libraryNameToBeBuilt="${2}"
    local libraryBuildOption=

    case "${targetOption}" in
        wasm)
            libraryBuildOption="";;
        wasm-simd)
            libraryBuildOption="--simd";;
        wasm-mt)
            libraryBuildOption="--threads";;
        wasm-mt-simd)
            libraryBuildOption="--simd --threads";;
        wasm-shared)
            libraryBuildOption="--shared";;
        wasm-side-module)
            libraryBuildOption="--side-module";;
    esac

    function emlib_build() {
        ./emlib.sh build ${libraryBuildOption} --build-dir-name "build-${targetOption}" $@
    }

    case "${libraryNameToBeBuilt}" in
        zlib)
            emlib_build zlib
            cp lib/libz.a       ../../../Siv3D/lib/Web/${targetOption}/zlib/;;
        png)
            emlib_build libpng
            cp lib/libpng.a     ../../../Siv3D/lib/Web/${targetOption}/png/;;
        freetype)
            emlib_build freetype
            cp lib/libfreetype.a ../../../Siv3D/lib/Web/${targetOption}/freetype/;;
        harfbuzz)
            emlib_build harfbuzz
            cp lib/libharfbuzz.a ../../../Siv3D/lib/Web/${targetOption}/harfbuzz/;;
        giflib)
            emlib_build giflib
            cp lib/libgif.a     ../../../Siv3D/lib/Web/${targetOption}/giflib/;;
        opencv)
            emlib_build opencv
            cp lib/libopencv_core.a         ../../../Siv3D/lib/Web/${targetOption}/opencv/
            cp lib/libopencv_imgproc.a      ../../../Siv3D/lib/Web/${targetOption}/opencv/
            cp lib/libopencv_objdetect.a    ../../../Siv3D/lib/Web/${targetOption}/opencv/
            cp lib/libopencv_photo.a        ../../../Siv3D/lib/Web/${targetOption}/opencv/;;
        giflib)
            emlib_build giflib
            cp lib/libgif.a     ../../../Siv3D/lib/Web/${targetOption}/giflib/;;
        opus)
            emlib_build ogg opus opusfile
            cp lib/libopus.a        ../../../Siv3D/lib/Web/${targetOption}/opus/
            cp lib/libopusfile.a    ../../../Siv3D/lib/Web/${targetOption}/opus/;;
        tiff)
            emlib_build libtiff
            cp lib/libtiff.a    ../../../Siv3D/lib/Web/${targetOption}/tiff/;;
        turbojpeg)
            emlib_build turbojpeg
            cp lib/libturbojpeg.a  ../../../Siv3D/lib/Web/${targetOption}/turbojpeg/;;
        webp)
            emlib_build webp
            cp lib/libwebp.a    ../../../Siv3D/lib/Web/${targetOption}/webp/;;
        SDL2)
            echo "Now Preparing... Skip.";;
        *)
            echo "Not recognized library name: ${1}... Skip.";;
    esac
}

function main() {
    init

    local libs=(
        "zlib"
        "png"
        "freetype"
        "harfbuzz"
        "giflib"
        "opencv"
        "opus"
        "tiff"
        "turbojpeg"
        "webp"
    )

    local targets=(
        "wasm"
        "wasm-simd"
        "wasm-mt"
        "wasm-mt-simd"
        "wasm-shared"
        "wasm-side-module"
    )

    for target in ${targets[@]}; do
        for elem in ${libs[@]}; do
            build $target $elem
        done
    done
}

main
