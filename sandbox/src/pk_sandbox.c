#include "pk_sandbox.h"

#include <core/pk_logger.h>

internal b8
sandbox_initialize(game *game_inst) {
    return true;
}

internal b8
sandbox_update(game *game_inst, f64 delta_time) {
    return true;
}

internal b8
sandbox_render(game *game_inst, f64 delta_time) {
    return true;
}

internal b8
sandbox_on_resize(game *game_inst, u32 width, u32 height) {
    return true;
}