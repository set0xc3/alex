#pragma once

#include "defines.h"

struct game;

typedef struct application_config {
    i16 pos_x;
    i16 pos_y;
    i16 width;
    i16 height;
    char *name;
} application_config;

API b8 application_create(struct game *game_inst);
API b8 application_run();