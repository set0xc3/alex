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
    game_on_startup();
    
    while (!g_app.quit)
    {
        if (!window_handle_input(&g_app.window))
            g_app.quit = true;
        
        game_on_input();
        game_on_update(0.0);
        
        window_update(&g_app.window);
        
        usleep(1);
    }
    
    game_on_shutdown();
}