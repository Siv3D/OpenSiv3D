#!/bin/bash

cd src/MessageBox

emcmake cmake .. -DSIV3D_SOURCE=MessageBox/Main.cpp
make -j4
