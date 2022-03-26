#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"

extern b8 create_game(game *out_game);

int main(void) {
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

    return 0;
}