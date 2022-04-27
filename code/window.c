#include "window.h"

b8 
window_create(SDL_Window *window, const char *title,
              const i32 width, const i32 height, 
              const i32 window_flags)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // Default OpenGL is fine.
    SDL_GL_LoadLibrary(0);
    
    // Create Window
    window = SDL_CreateWindow("SDL Tutorial", 
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              width, height, 
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
    
    // NOTE(alex): Renderer
#if 0
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
#endif
    
    // Use Vsync
    if(SDL_GL_SetSwapInterval(true) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

b8 
window_destroy(SDL_Window *window)
{
    return true;
}

void 
window_update(SDL_Window *window)
{
    SDL_GL_SwapWindow(window);
}
