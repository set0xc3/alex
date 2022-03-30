#ifndef PK_ENTRY_POINT_H
#define PK_ENTRY_POINT_H

#include "core/pk_application.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "pk_defines.h"
#include "pk_game_types.h"

extern b8 create_game(game *out_game);

int main(void) {
    initialize_memory();

    game game_inst;
    if (!create_game(&game_inst)) {
        LOG_FATAL("create_game failed.");
        return -1;
    }

    if (
        !game_inst.initialize ||
        !game_inst.update ||
        !game_inst.render ||
        !game_inst.on_resize) {
        LOG_FATAL("The game's function pointers must be assigned.");
        return -2;
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        LOG_ERROR("Applicaion failed to create.");
        return 1;
    }

    // The main game loop.
    if (!application_run()) {
        LOG_ERROR("Applicaion did not shutdown gracefully.");
        return 2;
    }

    shutdown_memory();

    return 0;
}

#endif  // PK_ENTRY_POINT_H
