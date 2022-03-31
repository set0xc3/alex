#ifndef PK_ENTRY_POINT_H
#define PK_ENTRY_POINT_H

#include "core/pk_application.h"
#include "core/pk_assert.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "pk_defines.h"
#include "pk_game_types.h"

extern b8 create_game(game *out_game);

int main(void) {
    memory_initialize();

    game game_inst;
    memory_set(&game_inst, 0, sizeof(game_inst));

    if (!create_game(&game_inst)) {
        ASSERT_MSG(false, "create_game failed.");
    }

    if (
        !game_inst.initialize ||
        !game_inst.update ||
        !game_inst.render ||
        !game_inst.on_resize) {
        ASSERT_MSG(false, "The game's function pointers must be assigned.");
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        ASSERT_MSG(false, "Applicaion failed to create.");
    }

    // The main game loop.
    if (!application_run()) {
        ASSERT_MSG(false, "Applicaion did not shutdown gracefully.");
    }

    memory_shutdown();

    return 0;
}

#endif // PK_ENTRY_POINT_H
