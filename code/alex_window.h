#ifndef ALEX_WINDOW_H
#define ALEX_WINDOW_H

#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct Window_Data
{
    i32 x;
    i32 y;
    i32 width;
    i32 height;
    u32 flags;
    char title[MAX_STR_LEN];
};

struct Window_State
{
    SDL_Window *window;
    SDL_GLContext gl_context;
};

internal b8 window_init         (Window_State *window);
internal void window_update     (Window_State *window);
internal b8 window_handle_event (Input_State *input);

#endif // ALEX_WINDOW_H