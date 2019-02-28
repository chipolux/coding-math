#!/bin/bash
set -e

mkdir -p bin

echo "Build ep02"
clang++ ep02.cpp -lSDL2 -lSDL2_gfx -Wall -Werror -o bin/ep02

echo "Build ep03"
clang++ ep03.cpp -lSDL2 -lSDL2_gfx -Wall -Werror -o bin/ep03

echo "Build ep04"
clang++ ep04.cpp -lSDL2 -lSDL2_gfx -Wall -Werror -o bin/ep04
