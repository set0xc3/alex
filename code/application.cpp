
#include "application.h"

#include <stdio.h>

#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

global_variable SDL_Window* window;
global_variable SDL_GLContext context;
global_variable bool quit;

global_variable i32 screen_width = 1280;
global_variable i32 screen_height = 720;

namespace Alex
{
    bool Application::run()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        SDL_GL_LoadLibrary(0); // Default OpenGL is fine.
        
        // Create Window
        u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        window = SDL_CreateWindow(
                                  "SDL Tutorial", 
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                  screen_width, screen_height, 
                                  window_flags);
        if(!window)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        
        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        //Create context
        context = SDL_GL_CreateContext(window);
        if(!context)
        {
            printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        
        // Check OpenGL properties
        printf("OpenGL loaded\n");
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        printf("Vendor:   %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version:  %s\n", glGetString(GL_VERSION));
        
        // Initialize GLAD 
        if (!gladLoadGL())
        {
            printf("Failed to initialize GLAD\n");
            return false;
        }
        
        // Use Vsync
        if(SDL_GL_SetSwapInterval(true) < 0)
        {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        
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
                        //input_update_keyboard(event.key.keysym.sym, false);
                        break;
                    }
                    
                    //  ButtonState
                    case SDL_MOUSEBUTTONDOWN: {
                        //input_update_mouse(event.button.button, true);
                        break;
                    }
                    case SDL_MOUSEBUTTONUP: {
                        //input_update_mouse(event.button.button, false);
                        break;
                    }
                    
                    default:
                    break;
                }
            }
            
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            SDL_GL_SwapWindow(window);
            
            SDL_Delay(1);
        }
        
        return true;
    }
}