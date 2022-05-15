#include "alex_platform.h"

#include <SDL2/SDL.h>

internal void
platform_delay(u32 ms)
{
    SDL_Delay(ms);
}