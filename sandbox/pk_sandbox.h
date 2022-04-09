#ifndef PK_SANDBOX_H
#define PK_SANDBOX_H

#include <pk_defines.h>
#include <pk_game_types.h>

struct Sandbox_State {
    f64 delta_time;
};

bool sandbox_initialize();
bool sandbox_update(f64 delta_time);
bool sandbox_render(f64 delta_time);
bool sandbox_on_resize(i32 width, i32 height);

#endif
