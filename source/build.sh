#!/bin/sh

set -xe

g++ -ggdb `pkg-config --cflags SDL2_ttf SDL2 SDL2_image SDL2_mixer openssl libcurl` -o bin/program.exe main.cpp `pkg-config --libs SDL2_ttf SDL2 SDL2_image SDL2_mixer openssl libcurl`