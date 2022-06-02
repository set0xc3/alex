/* date = June 2nd 2022 1:25 pm */

#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

#include "alex_game.h"
#include "alex_graphics.h"

struct application_context
{
    b8 quit;
    
    game_context game;
    graphics_context graphics;
};

internal void startup_application();
internal void shutdown_application();

internal void application_run();

#endif //ALEX_APPLICATION_H
