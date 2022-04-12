@echo off
REM usage: <script> [build_path | type_build]
REM Build script for engine

SetLocal EnableDelayedExpansion

set name_dir=engine
set root_dir=""

pushd %~dp0%
cd ..\..
set root_dir=%cd%
popd

set build_path=%1%
set type_build=%2%

REM Get a list of all the .c/.cpp files.
set cpp_files=
for /R "%root_dir%\%name_dir%" %%f in (*.cpp) do (
    set cpp_files=!cpp_files! %%f
)
for /R "%root_dir%\third-party" %%f in (*.c) do (
    set cpp_files=!cpp_files! %%f 
)

set assembly=engine
set compiler_flags=-O0 -g -Wvarargs -Wall -Wextra
if "%type_build%" == "release" set compiler_flags=-O3 -DNDEBUG -Wvarargs -Wall -Wextra

set include_flags=-I"%root_dir%\%name_dir%" -I"%root_dir%\third-party\glad\include"
set linker_flags=-lUser32 -lOpengl32 -lGdi32 
set defines=-D_DEBUG -DPK_EXPORT -D_CRT_SECURE_NO_WARNINGS

echo "Building %assembly%%..."
clang %cpp_files% %compiler_flags% -o "%build_path%\%assembly%.exe" %defines% %include_flags% %linker_flags%