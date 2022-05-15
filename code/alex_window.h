#ifndef ALEX_WINDOW_H
#define ALEX_WINDOW_H

#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct Window_Data
{
    i32 x, y;
    i32 width, height;
    u32 flags;
    char title[MAX_STR_LEN];
};

class Window
{
    public:
    
    void init();
    void update();
    b8 handle_event();
    
    void set_visible(const b8 visible);
    void set_vsync(const b8 interval);
    
    private:
    
    SDL_Window *window;
    SDL_GLContext gl_context;
};

#endif // ALEX_WINDOW_H