#ifndef PK_WINDOW_H
#define PK_WINDOW_H

#include "pk_defines.h"

struct Window_State
{
    void *internal_state;
};

bool window_initialize(Window_State *window, const char *title, i32 pos_x, i32 pos_y, i32 width, i32 height);
bool window_shutdown(Window_State *window);
bool window_poll_message();
void window_update(Window_State *window);

#endif /* PK_WINDOW_H */
