#include "alex_application.h"

global_variable application_context g_app;

internal void 
init_application()
{
    create_window(&g_app.window);
}

internal void 
application_run()
{
    while (!g_app.quit)
    {
        if (!window_process_event(&g_app.window))
            g_app.quit = true;
        
        window_update(&g_app.window);
        
        usleep(1);
    }
}