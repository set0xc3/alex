#pragma once

#include "defines.h"

typedef struct platform_state {
    void *internal_state;
} platform_state;

b8 platform_startup(
    platform_state *platform,
    const char *title,
    i32 pos_x,
    i32 pos_y,
    i32 width,
    i32 height);
b8 platform_shutdown(platform_state *platform);
b8 platform_poll_message(platform_state *platform);