
/* Index of this file:
     
[SECTION] Headers
      [SECTION] Global variable
 
*/

/* TODO:

# Core:
 - Logger
- Time
- String
- Dynamic Arrays
- Memory
- Jobs
- Threads
 - Collision

# Systems:
- Input
- Event
- Audio
- Network
- Graphics
- Resources
- IMGUI/GUI
- Physics
 - Profiler
- AI

# Tools:
- Sandbox
- Editor

*/

//-----------------------------------------------
// [SECTION] Headers
//-----------------------------------------------

// Standard headers
#include <stdio.h> // printf

// Basic types
#include "alex.h"
#include "events.h"
#include "mouse.h"
#include "window.h"

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//-----------------------------------------------
// [SECTION] Global variable
//-----------------------------------------------

global_variable b8 quit = false;

// Window
global_variable SDL_Window *window = 0;
global_variable SDL_GLContext context = 0;
global_variable char *window_title = "Engine";

global_variable i32 screen_width = 1280;
global_variable i32 screen_height = 720;

// Mouse
global_variable Mouse_t mouse;

int 
main(void)
{
    mouse_init(&mouse);
    
    u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window_create(window, window_title,
                  screen_width, screen_height, 
                  window_flags);
    
    while (!quit)
    {
        mouse_pre_poll(&mouse);
        
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                
                // KeyState
                case  SDL_KEYDOWN: {
                    break;
                }
                case SDL_KEYUP: {
                    break;
                }
                
                //  ButtonState
                case SDL_MOUSEBUTTONDOWN: {
                    mouse_on_button_down(&mouse, event.button.button);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    mouse_on_button_up(&mouse, event.button.button);
                    break;
                }
                
                default:
                break;
            }
        }
        mouse_post_poll(&mouse);
        
        // NOTE(alex): Remove this
        if (mouse_is_down(&mouse, 1)){
            //SDL_Log("mouse:left:down");
        }
        if (mouse_is_pressed(&mouse, 1)){
            SDL_Log("mouse:left:pressed");
        }
        if (mouse_is_released(&mouse, 1)){
            SDL_Log("mouse:left:released");
        }
        
        
        // NOTE(alex): Renderer
#if 0
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
#endif
        
        window_update(window);
        
        SDL_Delay(1);
        
    }
    
    return 0;
}