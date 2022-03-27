#if !defined(PEKORA_APPLICATION_H)
#define PEKORA_APPLICATION_H

#include "pekora_defines.h"

struct game;

typedef struct application_config {
    i16 pos_x;
    i16 pos_y;
    i16 width;
    i16 height;
    char *name;
} application_config;

PEKORA_API b8 application_create(struct game *game_inst);
PEKORA_API b8 application_run();

#endif  // PEKORA_APPLICATION_H