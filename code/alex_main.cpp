#include "alex_application.h"
#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_renderer.h"
#include "alex_sandbox.h"
#include "alex_shader.h"

int 
main(void)
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    // Load Modules
    logger_init();
    input_init(&app.input);
    window_init(&app.window);
    renderer_init(&app.renderer);
    sandbox_init(&app);
    
    // MainLoop
    app.running = true;
    while (app.running)
    {
        input_reset(&app.input);
        if (!window_handle_event(&app.input))
        {
            app.running = false;
            break;
        }
        input_update(&app.input);
        
        // Update modules
        sandbox_on_event(&app);
        sandbox_on_update(&app);
        sandbox_on_render(&app);
        
        window_update(&app.window);
        
        SDL_Delay(1);
    }
    
    return 0;
}