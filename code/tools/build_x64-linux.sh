#!/bin/bash

root=/home/cpp/Projects/alex

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
-lSDL2
"

binary=$root/build/sandbox
flags="-O0 -g"

clang $files $includes $flags $libs -o $binary
