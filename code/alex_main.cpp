#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_renderer.h"
#include "alex_sandbox.h"

int 
main(int argc, char *argv[])
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    // Load Modules
    
    // Test Log
#if 1
    LOG_INFO("PI: %f", PI);
    LOG_WARN("PI: %f", PI);
    LOG_DEBUG("PI: %f", PI);
    LOG_TRACE("PI: %f", PI);
    LOG_ERROR("PI: %f", PI);
    LOG_FATAL("PI: %f", PI);
#endif
    
    input_init(&app.input);
    window_init(&app.window);
    renderer_init(&app.renderer);
    sandbox_init(&app);
    
    // MainLoop
    app.running = true;
    while (app.running)
    {
        if (!window_handle_event(&app.input))
        {
            app.running = false;
            break;
        }
        
        // Update modules
        sandbox_on_event(&app);
        sandbox_on_update(&app);
        sandbox_on_render(&app);
        
        window_update(&app.window);
        
        //LOG_DEBUG("TEST");
        SDL_Delay(1000/144);
    }
    SDL_Quit();
    
    return 0;
}