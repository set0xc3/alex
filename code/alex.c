#include "alex.h"

/* Index of this file:
     
[SECTION] Headers
      [SECTION] Defines
[SECTION] Global variable
[SECTION] Input
 [SECTION] Window

*/

//-----------------------------------------------
// [SECTION] Input
//-----------------------------------------------

void 
input_init(InputContext *input)
{
    memset(input, 0, sizeof(*input));
}

void 
input_add_key_event(InputContext *input, const KeyCode key, const b8 down)
{
}

void 
input_add_mouse_button_event(InputContext *input, const MouseButton button, const b8 down)
{
    InputEvent e          = {};
    e.type                = InputEventType_MouseButton;
    e.source              = InputSource_Mouse;
    e.button.button       = button;
    e.button.down         = down;
    input->events         = e;
}

void 
input_add_character_event(InputContext *input, u8 c)
{
}

void 
input_update(InputContext *input)
{
    InputEvent *e = &input->events;
    if (e->source == MouseButton_Unknown)
    {
        return;
    }
    
    if (e->type == InputEventType_MouseButton)
    {
        memcpy(&input->mouse_prev_down, &input->mouse_down, sizeof(input->mouse_down));
        
        input->mouse_down[e->button.button] = e->button.down;
        input->mouse_pressed[e->button.button] = input->mouse_down[e->button.button] && !input->mouse_prev_down[e->button.button];
        input->mouse_released[e->button.button] = !input->mouse_down[e->button.button] && input->mouse_prev_down[e->button.button];
        
        //SDL_Log("button: %i", e->button.button);
        //SDL_Log("down: %i", input->mouse_down[e->button.button]);
        //SDL_Log("prev_down: %i", input->mouse_prev_down[e->button.button]);
        //SDL_Log("pressed: %i", input->mouse_pressed[e->button.button]);
        //SDL_Log("released: %i", input->mouse_released[e->button.button]);
    }
}

void 
input_reset(InputContext *input)
{
    memset(&input->mouse_pressed, 0, sizeof(*input->mouse_pressed));
    memset(&input->mouse_released, 0, sizeof(*input->mouse_released));
}

b8
input_is_key_down(const InputContext *input, const KeyCode key)
{
    return false;
}

b8
input_is_key_pressed(const InputContext *input, const KeyCode key)
{
    return false;
}

b8
input_is_key_released(const InputContext *input, const KeyCode key)
{
    return false;
}

b8
input_is_mouse_down(const InputContext *input, const MouseButton button)
{
    return input->mouse_down[button];
}

b8
input_is_mouse_pressed(const InputContext *input, const MouseButton button)
{
    return input->mouse_pressed[button];
}

b8
input_is_mouse_released(const InputContext *input, const MouseButton button)
{
    return input->mouse_released[button];
}

//-----------------------------------------------
// [SECTION] Window
//-----------------------------------------------

b8
window_init(WindowContext *context)
{
    memset(context, 0, sizeof(*context));
    
    WindowData wd;
    wd.title = "Engine";
    wd.x = 0;
    wd.y = 0;
    wd.width = 800;
    wd.height = 720;
    wd.flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL; 
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // Default OpenGL is fine.
    SDL_GL_LoadLibrary(0);
    
    // Create Window
    context->window = SDL_CreateWindow(wd.title, 
                                       wd.x,wd.y, 
                                       wd.width, wd.height, 
                                       wd.flags);
    if(!context->window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    // Use Vsync
    if(SDL_GL_SetSwapInterval(true) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

void 
window_update(WindowContext *context)
{
    SDL_GL_SwapWindow(context->window);
}

b8 
window_event_poll(InputContext *input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        switch (event.type) 
        {
            case SDL_QUIT: {
                return false;
            }
            
            // KeyState
            case  SDL_KEYDOWN:{
                break;
            }
            case SDL_KEYUP:{
                break;
            }
            
            //  ButtonState
            case SDL_MOUSEBUTTONDOWN:
            {
                MouseButton button;
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:   button = MouseButton_Left;   break;
                    case SDL_BUTTON_MIDDLE: button = MouseButton_Middle; break;
                    case SDL_BUTTON_RIGHT:  button = MouseButton_Right;  break;
                    default: button = MouseButton_Unknown; break;
                }
                input_add_mouse_button_event(input, button, true);
                //SDL_Log("button:down: %i", button);
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                MouseButton button;
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:   button = MouseButton_Left;   break;
                    case SDL_BUTTON_MIDDLE: button = MouseButton_Middle; break;
                    case SDL_BUTTON_RIGHT:  button = MouseButton_Right;  break;
                    default: button = MouseButton_Unknown; break;
                }
                input_add_mouse_button_event(input, button, false);
                //SDL_Log("button:up: %i", button);
                break;
            }
            
            default:
            break;
        }
    }
    
    return true;
}