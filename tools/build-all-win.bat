@echo off
REM Build Everything
REM usage: <script> [type_build | platform]

set root_dir=""

pushd %~dp0%
cd ..
set root_dir=%cd%
popd

set type_build=debug
if "%1%" == "release" set type_build=release

set platform=x64
if "%2%" == "x86" set platform=x86

if not exist "%root_dir%\build" mkdir "%root_dir%\build"
if not exist "%root_dir%\build\%type_build%" mkdir "%root_dir%\build\%type_build%"
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)


echo "Building..."
pushd "%root_dir%\code\tools"
call build_%platform%-win.bat "%root_dir%\build\%type_build%" %type_build%
popd
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

echo "Successfully."