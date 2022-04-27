#ifndef ALEX_WINDOW_H
#define ALEX_WINDOW_H

#include "alex.h"

// OpenGL Extensions
//#include <glad/glad.h>

#include <SDL2/SDL.h>

b8 window_create(SDL_Window *window, const char *title,
                 const i32 width, const i32 height, 
                 const i32 window_flags);

b8 window_destroy(SDL_Window *window);

void window_update(SDL_Window *window);

#endif
