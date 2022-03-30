#ifndef PK_SANDBOX_H
#define PK_SANDBOX_H

#include <pk_defines.h>
#include <pk_game_types.h>

typedef struct sandbox_state {
    f32 delta_time;
} sandbox_state;

b8 sandbox_initialize(game *game_inst);
b8 sandbox_update(game *game_inst, f32 delta_time);
b8 sandbox_render(game *game_inst, f32 delta_time);
b8 sandbox_on_resize(game *game_inst, u32 width, u32 height);

#endif  // PK_SANDBOX_H
