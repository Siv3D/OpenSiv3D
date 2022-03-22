#!/bin/bash

cd src/TextInput

emcmake cmake .. -DSIV3D_SOURCE=TextInput/Main.cpp
make -j4
