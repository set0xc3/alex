#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_world.h"

struct Game_State
{
    Game_World world;
};

struct Application
{
    b8 running;
    
    Input_State input;
    Window_State window;
    Game_State game;
};

int 
main(void)
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    logger_init();
    input_init(&app.input);
    window_init(&app.window);
    
    app.running = true;
    while (app.running)
    {
        if (!window_handle_event(&app.input))
        {
            app.running = false;
            break;
        }
        
        input_update(&app.input);
        window_update(&app.window);
        
        if (input_is_mouse_pressed(&app.input, MouseButton_Left))
            LOG_DEBUG("pressed");
        if (input_is_mouse_released(&app.input, MouseButton_Left))
            LOG_DEBUG("released");
        
        for (i64 i = 0; i < 256; ++i)
        {
            if (input_is_key_pressed(&app.input, (Key_Code)i))
                LOG_DEBUG("pressed");
            if (input_is_key_released(&app.input, (Key_Code)i))
                LOG_DEBUG("released");
        }
        
        input_reset(&app.input);
        SDL_Delay(1);
    }
    
    return 0;
}