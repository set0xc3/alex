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
    
    input_init(&context.input);
    window_init(&context.window);
    
    while (!context.quit)
    {
        if (!window_event_poll(&context.input))
        {
            context.quit = true;
            break;
        }
        
        input_update(&context.input);
        window_update(&context.window);
        
        if (input_is_mouse_pressed(&context.input, MouseButton_Left))
            SDL_Log("pressed");
        if (input_is_mouse_released(&context.input, MouseButton_Left))
            SDL_Log("released");
        
        for (i64 i = 0; i < 256; ++i)
        {
            if (input_is_key_pressed(&context.input, i))
                SDL_Log("pressed");
            if (input_is_key_released(&context.input, i))
                SDL_Log("released");
        }
        
        input_reset(&context.input);
        SDL_Delay(1);
    }
    
    return 0;
}