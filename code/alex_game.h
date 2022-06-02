/* date = June 2nd 2022 5:43 pm */

#ifndef ALEX_GAME_H
#define ALEX_GAME_H

struct game_context
{
    
};

internal void game_startup(game_context *context);
internal void game_shutdown(game_context *context);

internal void game_update(game_context *context, f64 dt);
internal void game_handle_input(game_context *context);

#endif //ALEX_GAME_H
