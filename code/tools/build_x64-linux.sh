#!/bin/bash

root=/home/cpp/Projects/alex

files="
$root/code/main.c
$root/code/window.c

$root/third-party/glad/src/glad.c
"

includes="
-I$root/third-party/glad/include/ 
-I$root/third-party/glm/
"

# -lstdc++

libs="
-lm
-lGL 
-lSDL2
"

binary=$root/build/sandbox
flags="-O0 -g"

clang $files $includes $flags $libs -o $binary
