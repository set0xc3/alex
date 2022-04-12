#ifndef PK_ENTRY_POINT_H
#define PK_ENTRY_POINT_H

#include "core/pk_application.h"
#include "core/pk_assert.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "pk_defines.h"

bool 
init()
{
    memory_init();
    
    // Initialization.
    if (!application_create())
    {
        ASSERT_MSG(false, "Applicaion failed to create.");
        return false;
    }
    
    // The main game loop.
    if (!application_run()) 
    {
        ASSERT_MSG(false, "Applicaion did not shutdown gracefully.");
        return false;
    }
    
    memory_shutdown();
    
    return true;
}

#if PK_PLATFORM_WINDOWS

#include "windows.h"

int WINAPI 
WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, PSTR lp_cmd_line, int  n_cmd_show)
{
    init();
    
    return 0;
}
#else
int main(void)
{
    init();
    return 0;
}
#endif /* PK_PLATFORM_WINDOWS */

#endif /* PK_ENTRY_POINT_H */
