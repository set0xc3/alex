#!/bin/bash

root=$PWD

files="
$root/code/alex.cpp

$root/third-party/imgui/imgui.cpp
$root/third-party/imgui/imgui_demo.cpp
$root/third-party/imgui/imgui_draw.cpp
$root/third-party/imgui/imgui_tables.cpp
$root/third-party/imgui/imgui_widgets.cpp
$root/third-party/imgui/backends/imgui_impl_glfw.cpp
$root/third-party/imgui/backends/imgui_impl_opengl3.cpp
"

includes="
-I$root/third-party/glm/

-I$root/third-party/imgui/
-I$root/third-party/imgui/backends/
"

libs="
-lGL
-lglfw
-lm
-lX11
"

binary=$root/build/sandbox
flags="-std=c++11 -O0 -g3"

mkdir -p $root/build/
clang++ $files $includes $flags $libs -o $binary