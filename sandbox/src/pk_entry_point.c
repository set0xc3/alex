#include <core/pk_memory.h>
#include <pk_entry_point.h>

#include "pk_sandbox.h"

// TODO(parsecffo): Remove this.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the funtion to create a game
internal b8
create_game(game *out_game) {
    // Application configuration.
    out_game->app_config.pos_x = 100;
    out_game->app_config.pos_y = 100;
    out_game->app_config.width = 1280;
    out_game->app_config.height = 720;
    out_game->app_config.name = "Pekora Engine(Sandbox)";

    out_game->initialize = sandbox_initialize;
    out_game->update = sandbox_update;
    out_game->render = sandbox_render;
    out_game->on_resize = sandbox_on_resize;

    // Create the game state.
    out_game->state = pk_allocate(sizeof(sandbox_state), MEMORY_TAG_GAME);

    return true;
}