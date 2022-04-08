@ECHO OFF
REM Build Everything


ECHO "Building everything..."

PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD sandbox
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

: REM Engine
: make -f "Makefile.engine.windows.mak" all
: IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

: REM sandbox
: make -f "Makefile.sandbox.windows.mak" all
: IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

: REM Tests
: make -f "Makefile.tests.windows.mak" all
: IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully."