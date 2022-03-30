#include "pk_common.h"

#if PK_PLATFORM_WINDOWS

#include <windows.h>

internal void
sleep(u64 ms) {
    Sleep(ms);
}

#endif