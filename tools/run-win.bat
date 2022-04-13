@echo off
REM usage: <script> [assembly | type_build]

set root_dir=""

pushd %~dp0%
cd ..
set root_dir=%cd%
popd

set assembly=alex
set type_build=debug
if "%2%" == "release" set type_build=release

if exist "%root_dir%\build\%type_build%" call "%root_dir%\build\%type_build%\%assembly%.exe"
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)