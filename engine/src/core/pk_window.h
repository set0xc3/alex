#ifndef PK_WINDOW_H
#define PK_WINDOW_H

#include "pk_defines.h"

typedef struct window_state {
    void* internal_state;
} window_state;

b8 window_initialize(
    window_state* platform,
    const char* title,
    i32 pos_x,
    i32 pos_y,
    i32 width,
    i32 height);
b8 window_shutdown(window_state* platform);
b8 window_poll_message();

#endif // PK_WINDOW_H
