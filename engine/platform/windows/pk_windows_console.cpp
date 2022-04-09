#include "core/pk_console.h"
#include "core/pk_assert.h"

#if PK_PLATFORM_WINDOWS

#include <windows.h>
#include <stdio.h>

global FILE* g_console_buffer = 0;
HANDLE console_handle = 0;

internal bool
console_init()
{
    if (!AllocConsole()) 
    {
        ASSERT_MSG(false, "AllocConsole failed!");
        return false;
    }
    
    if (freopen_s(&g_console_buffer, "CONOUT$", "w", stdout))
    {
        ASSERT_MSG(false, "freopen_s failed!");
        return false;
    }
    
    return true;
}

internal void
console_write(const char *msg, u8 colour)
{
    console_handle = GetStdHandle (STD_OUTPUT_HANDLE);
    
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    local u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
    SetConsoleTextAttribute (console_handle, levels[colour]);
    OutputDebugStringA (msg);
    u64 length = strlen (msg);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle (STD_OUTPUT_HANDLE), msg, (DWORD)length,
                  number_written, 0);
}

internal void
console_write_error(const char *msg, u8 colour)
{
    console_handle = GetStdHandle (STD_ERROR_HANDLE);
    
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    local u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
    SetConsoleTextAttribute (console_handle, levels[colour]);
    OutputDebugStringA (msg);
    u64 length = strlen (msg);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle (STD_ERROR_HANDLE), msg, (DWORD)length,
                  number_written, 0);
}

internal bool
console_shutdown()
{
    if (fclose(g_console_buffer)) 
    {
        ASSERT_MSG(false, "fclose failed!");
        return false;
    }
    FreeConsole();
    return true;
}

#endif