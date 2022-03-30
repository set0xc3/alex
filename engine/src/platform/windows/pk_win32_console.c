#include "core/pk_console.h"

#if PK_PLATFORM_WINDOWS

#include <windows.h>

internal void
console_write(const char* msg, u8 colour) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    local u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(msg);
    u64 length = strlen(msg);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)length, number_written, 0);
}

internal void
console_write_error(const char* msg, u8 colour) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);

    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    local u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(msg);
    u64 length = strlen(msg);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)length, number_written, 0);
}

#endif