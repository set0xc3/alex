#include "pk_application.h"

#include "core/pk_window.h"
#include "pk_assert.h"
#include "pk_common.h"
#include "pk_game_types.h"
#include "pk_logger.h"
#include "pk_memory.h"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended;
    i16 width;
    i16 height;
    f64 last_time;
    game *game_inst;
    window_state window_state;
} application_state;

global b8 initialized = false;
global application_state app_state;

b8 application_create(game *game_inst) {
    if (initialized) {
        LOG_ERROR("application_create failed.");
        return false;
    }

    app_state.game_inst = game_inst;

    // Initialize sybsystems.
    logger_initialize();

    // TODO(parsecffo): Remove this.
    LOG_FATAL("Message: %f", 3.14f);
    LOG_ERROR("Message: %f", 3.14f);
    LOG_WARN("Message: %f", 3.14f);
    LOG_INFO("Message: %f", 3.14f);
    LOG_DEBUG("Message: %f", 3.14f);
    LOG_TRACE("Message: %f", 3.14f);

    app_state.is_running = true;
    app_state.is_suspended = false;

    if (!window_initialize(
            &app_state.window_state,
            game_inst->app_config.name,
            game_inst->app_config.pos_x,
            game_inst->app_config.pos_y,
            game_inst->app_config.width,
            game_inst->app_config.height)) {
        LOG_ERROR("window_initialize failed.");
        return false;
    }

    // Initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        LOG_FATAL("Game failed to initialize.");
        return false;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = true;
    return true;
}

b8 application_run() {
    LOG_INFO(get_memory_usage_str());

    while (app_state.is_running) {
        if (!window_poll_message(&app_state.window_state)) {
            app_state.is_running = false;
        }

        if (!app_state.is_suspended) {
            app_state.game_inst->update(app_state.game_inst, (f32)0.f);
            app_state.game_inst->render(app_state.game_inst, (f32)0.f);
        }

        sleep(1);
    }

    window_shutdown(&app_state.window_state);
    app_state.is_running = false;
    return true;
}