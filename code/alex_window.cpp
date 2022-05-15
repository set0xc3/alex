#include "alex_window.h"

#include "alex_input.h"

internal void 
create_window(const Window_Data *wd, Window *window)
{
    window = (Window*)malloc(sizeof(Window));
    ZERO_STRUCT(window);
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("SDL_Init failed: %s", SDL_GetError());
        exit(-1);
    }
    
    // Create Window
    window->sdl_window = SDL_CreateWindow(wd->title, 
                                          wd->pos_x,wd->pos_y, 
                                          wd->width, wd->height, 
                                          SDL_WINDOW_OPENGL);
    if (!window->sdl_window)
    {
        LOG_ERROR("[SDL] Failed: %s", SDL_GetError());
        exit(-1);
    }
    
    window->gl_context = SDL_GL_CreateContext(window->sdl_window);
    if (!window->gl_context)
    {
        LOG_ERROR("[SDL] Failed: %s", SDL_GetError());
        exit(-1);
    }
    
    if (!gladLoadGL())
    {
        LOG_ERROR("[GLAD] Failed");
        exit(-1);
    }
    
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        // NOTE(alex): Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        i32 major;
        i32 minor;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
        LOG_INFO("OpenGL v%i.%i", major, minor);
    }
    
    window_set_vsync(window, true);
    window_set_visible(window, true);
}

internal void 
window_display(Window *window)
{
    SDL_GL_SwapWindow(window->sdl_window);
}

internal b8 
window_handle_event()
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
                Key_Code key = KeyCode_Unknown;
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
                break;
            }
            break;
            
            //  ButtonState
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                b8 down = false;
                Mouse_Button button = MouseButton_Unknown;
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:   button = MouseButton_Left;   break;
                    case SDL_BUTTON_MIDDLE: button = MouseButton_Middle; break;
                    case SDL_BUTTON_RIGHT:  button = MouseButton_Right;  break;
                }
                switch (event.button.type)
                {
                    case SDL_MOUSEBUTTONDOWN: down = true;  break;
                    case SDL_MOUSEBUTTONUP:   down = false; break;
                }
                break;
            }
            
            case SDL_MOUSEMOTION:
            {
                // TODO(alex): Callback
                //send((f32)event.motion.x, (f32)event.motion.y);  
                break;
            }
            
            case SDL_MOUSEWHEEL:
            {
                // TODO(alex): Callback
                //send((f32)event.wheel.x, (f32)event.wheel.y);  
                break;
            }
        }
    }
    
    return true;
}

internal void 
window_set_visible(Window *window, const b8 visible)
{
    if (visible)
        SDL_ShowWindow(window->sdl_window);
    else
        SDL_HideWindow(window->sdl_window);
}

internal void 
window_set_vsync(Window *window, const b8 interval)
{
    // Use Vsync
    if(SDL_GL_SetSwapInterval(interval) < 0)
    {
        LOG_WARN("Unable to set VSync: %s", SDL_GetError());
    }
}