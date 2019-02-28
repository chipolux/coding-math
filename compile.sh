#!/bin/bash
set -e

mkdir -p bin
clang++ ep02.cpp -lSDL2 -lSDL2_gfx -Wall -Werror -o bin/ep02
