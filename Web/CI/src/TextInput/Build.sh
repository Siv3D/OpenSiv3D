#!/bin/bash

cd src/TextInput

Siv3DRootPath=$(dirname $(pwd))/Package

emcmake cmake .. -DSIV3D_SOURCE=TextInput/Main.cpp -DCMAKE_PREFIX_PATH=${Siv3DRootPath} -DCMAKE_FIND_ROOT_PATH=${Siv3DRootPath}
make -j4
