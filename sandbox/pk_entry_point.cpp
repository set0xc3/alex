#include <core/pk_memory.h>
#include <pk_entry_point.h>

#include "pk_sandbox.h"

// TODO(parsecffo): Remove this.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the funtion to create a game
internal bool
create_game(Game *game)
{
    // Application configuration.
    game->app.pos_x = 1280 / 2;
    game->app.pos_y = 30;
    game->app.width = 1280;
    game->app.height = 720;
    game->app.name = "Pekora Engine(Sandbox)";
    
    game->initialize = sandbox_initialize;
    game->update = sandbox_update;
    game->render = sandbox_render;
    game->on_resize = sandbox_on_resize;
    
    // Create the game state.
    game->state = memory_allocate(sizeof(Sandbox_State), MemoryTag_Game);
    
    return true;
}