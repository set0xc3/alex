#include "sandbox.h"

#include <core/logger.h>

b8 sandbox_initialize(game *game_inst) {
    LOG_INFO("sandbox_initialize() called.")
    return true;
}

b8 sandbox_update(game *game_inst, f32 delta_time) {
    return true;
}

b8 sandbox_render(game *game_inst, f32 delta_time) {
    return true;
}

b8 sandbox_on_resize(game *game_inst, u32 width, u32 height) {
    return true;
}