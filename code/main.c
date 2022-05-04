#include "alex.h"

typedef struct AlexContext
{
    b8 quit;
    
    InputContext input;
    WindowContext window;
    
} AlexContext;

global_variable AlexContext context;

int 
main(void)
{
    memset(&context, 0, sizeof(context));
    
    logger_init();
    input_init(&context.input);
    window_init(&context.window);
    
    while (!context.quit)
    {
        if (!window_handle_event(&context.input))
        {
            context.quit = true;
            break;
        }
        
        input_update(&context.input);
        window_update(&context.window);
        
        if (input_is_mouse_pressed(&context.input, MouseButton_Left))
            LOG_DEBUG("pressed");
        if (input_is_mouse_released(&context.input, MouseButton_Left))
            LOG_DEBUG("released");
        
        for (i64 i = 0; i < 256; ++i)
        {
            if (input_is_key_pressed(&context.input, i))
                LOG_DEBUG("pressed");
            if (input_is_key_released(&context.input, i))
                LOG_DEBUG("released");
        }
        
        input_reset(&context.input);
        SDL_Delay(1);
    }
    
    return 0;
}