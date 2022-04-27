
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
- Editor
- Sandbox

*/

//-----------------------------------------------
// [SECTION] Headers
//-----------------------------------------------

// Standard headers
#include <stdio.h> // printf

// Basic types
#include "alex.h"
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

int 
main(void)
{
    u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window_create(window, window_title,
                  screen_width, screen_height, 
                  window_flags);
    
    while (!quit)
    {
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
                    //input_update_keyboard(event.key.keysym.sym, true);
                    break;
                }
                case SDL_KEYUP: {
                    //input_update_keyboard(event.key.keysym.sym, -1);
                    break;
                }
                
                //  ButtonState
                case SDL_MOUSEBUTTONDOWN: {
                    //input_update_mouse(event.button.button, true);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    //input_update_mouse(event.button.button, -1);
                    break;
                }
                
                default:
                break;
            }
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