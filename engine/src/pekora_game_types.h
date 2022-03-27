#if !defined(PEKORA_GAME_TYPES_H)
#define PEKORA_GAME_TYPES_H

#include "core/pekora_application.h"

typedef struct game {
    application_config app_config;
    b8 (*initialize)(struct game* game_inst);
    b8 (*update)(struct game* game_inst, f32 delta_time);
    b8 (*render)(struct game* game_inst, f32 delta_time);
    b8 (*on_resize)(struct game* game_inst, u32 width, u32 height);
    void* state;
} game;

#endif  // PEKORA_GAME_TYPES_H