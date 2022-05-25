#!/bin/bash

root=$PWD

files="
$root/code/alex.cpp
"

includes="
-I/usr/local/include/

-I$root/third-party/glm/
-I$root/third-party/imgui/
-I$root/third-party/imgui/backends
"

GL="
-lGL
`pkg-config --static --libs glfw3`
`pkg-config --cflags glfw3`
"

libs="
-L/usr/local/lib
-lm
-lX11
$GL
"

binary=$root/build/sandbox
flags="-std=c++11 -O0 -g3 -Wall -Wformat"

mkdir -p $root/build/
clang++ $files $includes $flags $libs -o $binary