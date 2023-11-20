#!/bin/sh

set -xe

g++ -ggdb `pkg-config --cflags --libs SDL2_ttf SDL2 SDL2_image SDL2_mixer openssl` -lcurl.dll -o program.exe main.cpp