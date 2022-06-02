#include "alex_application.h"

global_variable application_context g_app;

internal void 
startup_application()
{
    startup_graphics(&g_app.graphics);
}

internal void 
shutdown_application()
{
    g_app.quit = true;
}

internal void 
application_run()
{
    game_startup(&g_app.game);
    
    while (!g_app.quit)
    {
        if (!graphics_handle_input(&g_app.graphics))
            shutdown_application();
        
        game_handle_input(&g_app.game);
        game_update(&g_app.game, 0.0);
        
        graphics_update(&g_app.graphics);
        
        usleep(1);
    }
    
    game_shutdown(&g_app.game);
}