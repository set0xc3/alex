REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c files.
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f 
)

FOR /R ../third-party %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f 
)
REM SET cFilenames=!cFilenames! %../third-party/glad/src/glad.c

SET assembly=engine

: Debug
SET compilerFlags=-O0 -g -shared -Wvarargs -Wall -Wextra
: Release
@REM SET compilerFlags=-O3 -s -shared -DNDEBUG -Wvarargs -Wall -Wextra

SET includeFlags=-I./src -I../third-party/glad/include
SET linkerFlags=-lUser32 -lOpengl32 -lGdi32 
SET defines=-D_DEBUG -DPK_EXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%%..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%