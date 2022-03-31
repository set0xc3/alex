#include "core/pk_application.h"

#include "audio/pk_audio.h"
#include "core/pk_assert.h"
#include "core/pk_event.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "core/pk_window.h"
#include "pk_common.h"
#include "pk_game_types.h"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended;
    i16 width;
    i16 height;
    f64 last_time;
    game *game_inst;
    window_state window_state;
} application_state;

global b8 g_is_initialized = false;
global application_state g_app_state;

b8 application_create(game *game_inst) {
    if (g_is_initialized) {
        LOG_ERROR("application_create failed.");
        return false;
    }

    g_app_state.game_inst = game_inst;

    // Initialize sybsystems
    event_initialize();
    logger_initialize();

    // TODO(parsecffo): Remove this
    LOG_FATAL("Message: %f", 3.14f);
    LOG_ERROR("Message: %f", 3.14f);
    LOG_WARN("Message: %f", 3.14f);
    LOG_INFO("Message: %f", 3.14f);
    LOG_DEBUG("Message: %f", 3.14f);
    LOG_TRACE("Message: %f", 3.14f);

    g_app_state.is_running = true;
    g_app_state.is_suspended = false;

    if (!window_initialize(
            &g_app_state.window_state,
            game_inst->app_config.name,
            game_inst->app_config.pos_x,
            game_inst->app_config.pos_y,
            game_inst->app_config.width,
            game_inst->app_config.height)) {
        LOG_ERROR("window_initialize failed.");
        return false;
    }

    // Initialize the game
    if (!g_app_state.game_inst->initialize(g_app_state.game_inst)) {
        LOG_FATAL("Game failed to initialize.");
        return false;
    }

    g_app_state.game_inst->on_resize(g_app_state.game_inst, g_app_state.width, g_app_state.height);

    g_is_initialized = true;
    return true;
}

b8 application_run() {
    LOG_INFO(get_memory_usage_str());

    while (g_app_state.is_running) {
        if (!window_poll_message(&g_app_state.window_state)) {
            g_app_state.is_running = false;
        }

        if (!g_app_state.is_suspended) {
            g_app_state.game_inst->update(g_app_state.game_inst, (f32)0.f);
            g_app_state.game_inst->render(g_app_state.game_inst, (f32)0.f);
        }

        sleep(1);
    }

    // Shutdown subsystems
    event_shutdown();
    logger_shutdown();
    window_shutdown(&g_app_state.window_state);

    g_app_state.is_running = false;
    return true;
}