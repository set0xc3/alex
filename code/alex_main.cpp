#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_renderer.h"

struct Application_State
{
    b8 running;
    
    Input_State input;
    Window_State window;
    Renderer_State renderer;
};

int 
main(void)
{
    Application_State app;
    memset(&app, 0, sizeof(app));
    
    logger_init();
    input_init(&app.input);
    window_init(&app.window);
    renderer_init(&app.renderer);
    
    String_u8 string;
    
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
        
        renderer_draw(&app.renderer);
        
        window_update(&app.window);
        
        SDL_Delay(1);
    }
    
    return 0;
}