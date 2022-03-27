#if !defined(PEKORA_SANDBOX_H)
#define PEKORA_SANDBOX_H

#include <pekora_defines.h>
#include <pekora_game_types.h>

typedef struct sandbox_state {
    f32 delta_time;
} sandbox_state;

b8 sandbox_initialize(game *game_inst);
b8 sandbox_update(game *game_inst, f32 delta_time);
b8 sandbox_render(game *game_inst, f32 delta_time);
b8 sandbox_on_resize(game *game_inst, u32 width, u32 height);

#endif  // PEKORA_SANDBOX_H