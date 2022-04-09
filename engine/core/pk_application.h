#ifndef PK_APPLICATION_H
#define PK_APPLICATION_H

#include "pk_defines.h"

struct Game;

struct Application_Config
{
    i32 pos_x;
    i32 pos_y;
    i32 width;
    i32 height;
    char *name;
};

PK_API bool application_create(Game *game);
PK_API bool application_run();

#endif
