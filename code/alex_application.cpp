#include "alex_application.h"

global_variable application_context g_app;

internal void 
startup_application()
{
    create_window(&g_app.window);
    startup_renderer(&g_app.renderer);
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
        if (!window_handle_input(&g_app.window))
            shutdown_application();
        
        game_handle_input(&g_app.game);
        game_update(&g_app.game, 0.0);
        
        window_update(&g_app.window);
        
        usleep(1);
    }
    
    game_shutdown(&g_app.game);
    
    destroy_window(&g_app.window);
}