@echo off
REM usage: <script> [build_path | type_build]

SetLocal EnableDelayedExpansion

set root_dir=""

pushd %~dp0%
cd ..\..
set root_dir=%cd%
popd

set build_path=%1%
set type_build=%2%

set cpp_files="%root_dir%\code\alex_win32.cpp"

REM Get a list of all the .c/.cpp files.
REM for /R "%root_dir%\code" %%f in (*.cpp) do (
REM     set cpp_files=!cpp_files! %%f
REM )
REM Get a list of all the .c/.cpp files.
REM for /R "%root_dir%\third-party" %%f in (*.c) do (
REM     set cpp_files=!cpp_files! %%f 
REM )

REM -g -Wvarargs -Wall -Wextra

set assembly=alex
set compiler_flags=-O0 -g
if "%type_build%" == "release" set compiler_flags=-O3 -DNDEBUG

set include_flags=-I"%root_dir%\code" -I"%root_dir%\third-party\glad\include"
set linker_flags=-lUser32 -lOpengl32 -lGdi32 
set defines=-D_DEBUG -D_CRT_SECURE_NO_WARNINGS -DALEX_WIN32=1

clang %cpp_files% %compiler_flags% -o "%build_path%\%assembly%.exe" %defines% %include_flags% %linker_flags%