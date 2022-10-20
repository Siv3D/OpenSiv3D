#!/bin/bash

cd src/MessageBox

Siv3DRootPath=$(dirname $(pwd))/Package

emcmake cmake .. -DSIV3D_SOURCE=MessageBox/Main.cpp -DCMAKE_PREFIX_PATH=${Siv3DRootPath} -DCMAKE_FIND_ROOT_PATH=${Siv3DRootPath}
make -j4
