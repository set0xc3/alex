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
    InputEvent e  = {};
    e.type        = InputEventType_Key;
    e.source      = InputSource_Keyboard;
    e.key.key     = key;
    e.key.down    = down;
    input->events = e;
}

void 
input_add_mouse_button_event(InputContext *input, const MouseButton button, const b8 down)
{
    InputEvent e    = {};
    e.type          = InputEventType_MouseButton;
    e.source        = InputSource_Mouse;
    e.button.button = button;
    e.button.down   = down;
    input->events   = e;
}

void 
input_add_character_event(InputContext *input, u8 c)
{
    InputEvent e  = {};
    e.type        = InputEventType_Text;
    e.source      = InputSource_Keyboard;
    e.text.c      = c;
    input->events = e;
}

void 
input_update(InputContext *input)
{
    InputEvent *e = &input->events;
    
    if (e->source != MouseButton_Unknown && 
        e->type == InputEventType_MouseButton)
    {
        memcpy(&input->mouse_prev_down, &input->mouse_down, sizeof(input->mouse_down));
        
        input->mouse_down[e->button.button] = e->button.down;
        input->mouse_pressed[e->button.button] = input->mouse_down[e->button.button] && !input->mouse_prev_down[e->button.button];
        input->mouse_released[e->button.button] = !input->mouse_down[e->button.button] && input->mouse_prev_down[e->button.button];
    }
    else if (e->type == InputEventType_Key)
    {
        memcpy(&input->key_prev_down, &input->key_down, sizeof(input->key_down));
        
        input->key_down[e->key.key] = e->key.down;
        input->key_pressed[e->key.key] = input->key_down[e->key.key] && !input->key_prev_down[e->key.key];
        input->key_released[e->key.key] = !input->key_down[e->key.key] && input->key_prev_down[e->key.key];
    }
}

void 
input_reset(InputContext *input)
{
    memset(&input->mouse_pressed, 0, sizeof(*input->mouse_pressed));
    memset(&input->mouse_released, 0, sizeof(*input->mouse_released));
    
    memset(&input->key_pressed, 0, sizeof(*input->key_pressed));
    memset(&input->key_released, 0, sizeof(*input->key_released));
}

b8
input_is_key_down(const InputContext *input, const KeyCode key)
{
    return input->key_down[key];
}

b8
input_is_key_pressed(const InputContext *input, const KeyCode key)
{
    return input->key_pressed[key];
}

b8
input_is_key_released(const InputContext *input, const KeyCode key)
{
    return input->key_released[key];
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
            case SDL_QUIT: 
            {
                return false;
            }
            
            // KeyState
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                b8 down = false;
                KeyCode key = KeyCode_Unknown;
                switch (event.key.keysym.sym)
                {
                    case SDLK_0: key = KeyCode_0; break;
                    case SDLK_1: key = KeyCode_1; break;
                    case SDLK_2: key = KeyCode_2; break;
                    case SDLK_3: key = KeyCode_3; break;
                    case SDLK_4: key = KeyCode_4; break;
                    case SDLK_5: key = KeyCode_5; break;
                    case SDLK_6: key = KeyCode_6; break;
                    case SDLK_7: key = KeyCode_7; break;
                    case SDLK_8: key = KeyCode_8; break;
                    case SDLK_9: key = KeyCode_9; break;
                    
                    case SDLK_F1: key = KeyCode_F1; break;
                    case SDLK_F2: key = KeyCode_F2; break;
                    case SDLK_F3: key = KeyCode_F3; break;
                    case SDLK_F4: key = KeyCode_F4; break;
                    case SDLK_F5: key = KeyCode_F5; break;
                    case SDLK_F6: key = KeyCode_F6; break;
                    case SDLK_F7: key = KeyCode_F7; break;
                    case SDLK_F8: key = KeyCode_F8; break;
                    case SDLK_F9: key = KeyCode_F9; break;
                    case SDLK_F10: key = KeyCode_F10; break;
                    case SDLK_F11: key = KeyCode_F11; break;
                    case SDLK_F12: key = KeyCode_F12; break;
                    
                    case SDLK_a: key = KeyCode_A; break;
                    case SDLK_b: key = KeyCode_B; break;
                    case SDLK_c: key = KeyCode_C; break;
                    case SDLK_d: key = KeyCode_D; break;
                    case SDLK_e: key = KeyCode_E; break;
                    case SDLK_f: key = KeyCode_F; break;
                    case SDLK_g: key = KeyCode_G; break;
                    case SDLK_h: key = KeyCode_H; break;
                    case SDLK_i: key = KeyCode_I; break;
                    case SDLK_j: key = KeyCode_J; break;
                    case SDLK_k: key = KeyCode_K; break;
                    case SDLK_l: key = KeyCode_L; break;
                    case SDLK_m: key = KeyCode_M; break;
                    case SDLK_n: key = KeyCode_N; break;
                    case SDLK_o: key = KeyCode_O; break;
                    case SDLK_p: key = KeyCode_P; break;
                    case SDLK_q: key = KeyCode_Q; break;
                    case SDLK_r: key = KeyCode_R; break;
                    case SDLK_s: key = KeyCode_S; break;
                    case SDLK_t: key = KeyCode_T; break;
                    case SDLK_u: key = KeyCode_U; break;
                    case SDLK_v: key = KeyCode_V; break;
                    case SDLK_w: key = KeyCode_W; break;
                    case SDLK_x: key = KeyCode_X; break;
                    case SDLK_y: key = KeyCode_Y; break;
                    case SDLK_z: key = KeyCode_Z; break;
                }
                switch (event.key.type)
                {
                    case SDL_KEYDOWN: down = true;  break;
                    case SDL_KEYUP:   down = false; break;
                }
                input_add_key_event(input, key, down);
                break;
            }
            break;
            
            //  ButtonState
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                b8 down = false;
                MouseButton button = MouseButton_Unknown;
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:   button = MouseButton_Left;   break;
                    case SDL_BUTTON_MIDDLE: button = MouseButton_Middle; break;
                    case SDL_BUTTON_RIGHT:  button = MouseButton_Right;  break;
                }
                switch (event.key.type)
                {
                    case SDL_MOUSEBUTTONDOWN: down = true;  break;
                    case SDL_MOUSEBUTTONUP:   down = false; break;
                }
                input_add_mouse_button_event(input, button, down);
                break;
            }
        }
    }
    
    return true;
}