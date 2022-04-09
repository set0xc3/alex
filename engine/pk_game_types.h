#ifndef PK_GAME_TYPES_H
#define PK_GAME_TYPES_H

#include "core/pk_application.h"

struct Game
{
    Application_Config app;
    bool (*initialize)();
    bool (*update)(f64 delta_time);
    bool (*render)(f64 delta_time);
    bool (*on_resize)(i32 width, i32 height);
    void *state;
};

#endif
