#!/bin/bash

root=$PWD

files="
$root/code/alex.cpp
"

includes="
-I$root/third-party/glad/include/ 
-I$root/third-party/glm/
"

libs="
-lm
-lGL 
-lX11
-lSDL2
"

binary=$root/build/sandbox
flags="-O0 -g3"

mkdir -p $root/build/
clang++ $files $includes $flags $libs -o $binary
