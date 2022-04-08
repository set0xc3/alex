#ifndef PK_ENTRY_POINT_H
#define PK_ENTRY_POINT_H

#include "core/pk_application.h"
#include "core/pk_assert.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "pk_defines.h"
#include "pk_game_types.h"

extern b8 create_game(game *out_game);

b8 
init()
{
    memory_initialize();
    
    game game_inst = {};
    memory_set(&game_inst, 0, sizeof(game_inst));
    
    if (!create_game(&game_inst)) {
        ASSERT_MSG(false, "create_game failed.");
        return false;
    }
    
    if (!game_inst.initialize || !game_inst.update || !game_inst.render ||
        !game_inst.on_resize) {
        ASSERT_MSG(false, "The game's function pointers must be assigned.");
        return false;
    }
    
    // Initialization.
    if (!application_create(&game_inst)) {
        ASSERT_MSG(false, "Applicaion failed to create.");
        return false;
    }
    
    // The main game loop.
    if (!application_run()) {
        ASSERT_MSG(false, "Applicaion did not shutdown gracefully.");
        return false;
    }
    
    memory_shutdown();
    
    return true;
}

#if PK_PLATFORM_WINDOWS

#include "windows.h"

int WINAPI 
WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, PSTR lp_cmd_line, int  n_cmd_show)
{
    init();
    
    return 0;
}
#endif /* PK_PLATFORM_WINDOWS */

#endif /* PK_ENTRY_POINT_H */
