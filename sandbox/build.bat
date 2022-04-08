REM Build script for sandbox
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=sandbox

: Debug
SET compilerFlags=-O0 -g -Wvarargs -Wall -Wextra
: Release
@REM SET compilerFlags=-O3 -s -DNDEBUG -Wvarargs -Wall -WextraET compilerFlags=-g 
REM -Wvarargs -Wall -Werror -Wextra

SET includeFlags=-Isrc -I../engine/src/ 
SET linkerFlags=-L../bin/ -lengine.lib
SET defines=-D_DEBUG -DKIMPORT

ECHO "Building %assembly%%..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%