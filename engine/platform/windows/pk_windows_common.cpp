#include "pk_common.h"

#if PK_PLATFORM_WINDOWS

#include <windows.h>

internal void
wait_time(u64 ms)
{
    Sleep(ms);
}

#endif