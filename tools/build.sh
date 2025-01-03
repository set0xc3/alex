#!/bin/bash

root=$PWD

files="
$root/code/alex.cpp
"

includes="
-I/usr/local/include/

-I$root/third-party/glad/include/
-I$root/third-party/glm/
"
libs="
-L/usr/local/lib
-lm
-lX11
-lGL
"

binary=$root/build/sandbox
flags="-std=c++11 -O0 -g3"

mkdir -p $root/build/
clang++ $files $includes $flags $libs -o $binary