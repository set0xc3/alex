#include "core/pk_application.h"

#include "audio/pk_audio.h"
#include "core/pk_assert.h"
#include "core/pk_clock.h"
#include "core/pk_event.h"
#include "core/pk_input.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "core/pk_time.h"
#include "core/pk_window.h"
#include "pk_common.h"
#include "pk_game_types.h"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended;
    i16 width;
    i16 height;
    f64 last_time;
    clock clock;
    game *game_inst;
    window_state window_state;
} application_state;

global b8 g_initialized = false;
global application_state g_app_state = {};

b8 application_on_event(u16 code, void *sender, void *listener,
                        event_context event);

b8 application_create(game *game_inst) {
    if (g_initialized) {
        LOG_ERROR("application_create failed.");
        return false;
    }
    
    g_app_state.game_inst = game_inst;
    
    // Initialize sybsystems
    event_initialize();
    input_initialize();
    logger_initialize();
    
    event_register(EVENT_CODE_MOUSE_WHEEL, NULL, application_on_event);
    
    // TODO(parsecffo): Remove this
    LOG_FATAL("Message: %f", 3.14f);
    LOG_ERROR("Message: %f", 3.14f);
    LOG_WARN("Message: %f", 3.14f);
    LOG_INFO("Message: %f", 3.14f);
    LOG_DEBUG("Message: %f", 3.14f);
    LOG_TRACE("Message: %f\n", 3.14f);
    
    g_app_state.is_running = true;
    g_app_state.is_suspended = false;
    
    if (!window_initialize(
                           &g_app_state.window_state, game_inst->app_config.name,
                           game_inst->app_config.pos_x, game_inst->app_config.pos_y,
                           game_inst->app_config.width, game_inst->app_config.height)) {
        LOG_ERROR("window_initialize failed.");
        return false;
    }
    
    // Initialize the game
    if (!g_app_state.game_inst->initialize(g_app_state.game_inst)) {
        LOG_FATAL("Game failed to initialize.");
        return false;
    }
    
    g_app_state.game_inst->on_resize(g_app_state.game_inst, g_app_state.width,
                                     g_app_state.height);
    
    g_initialized = true;
    return true;
}

b8 application_run() {
    clock_start(&g_app_state.clock);
    clock_update(&g_app_state.clock);
    g_app_state.last_time = g_app_state.clock.elapsed;
    f64 running_time = 0;
    u8 frame_count = 0;
    f64 target_frame_seconds = 1.0f / 144;
    
    LOG_INFO(get_memory_usage_str());
    
    while (g_app_state.is_running) {
        // Update clock and get delta time
        clock_update(&g_app_state.clock);
        f64 current_time = g_app_state.clock.elapsed;
        f64 delta_time = (current_time - g_app_state.last_time);
        f64 frame_start_time = get_absolute_time();
        
        if (!window_poll_message(&g_app_state.window_state)) {
            g_app_state.is_running = false;
        }
        
        if (!g_app_state.is_suspended) {
            input_update(delta_time);
            g_app_state.game_inst->update(g_app_state.game_inst, delta_time);
            g_app_state.game_inst->render(g_app_state.game_inst, delta_time);
        }
        
        // Figure out how long frame took and, if below
        f64 frame_end_time = get_absolute_time();
        f64 frame_elapsed_time = frame_end_time - frame_start_time;
        running_time += frame_elapsed_time;
        f64 remaining_seconds = target_frame_seconds - frame_elapsed_time;
        if (remaining_seconds > 0) {
            u64 remaining_ms = (remaining_seconds * 1000);
            // If there if time left, give if back to the OS
            b8 limit_frames = true;
            if (remaining_ms > 0 && limit_frames) {
                sleep(remaining_ms - 1);
            }
            frame_count++;
        }
        
        // Update last time
        g_app_state.last_time = current_time;
    }
    
    clock_stop(&g_app_state.clock);
    
    // Shutdown subsystems
    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    
    event_shutdown();
    input_shutdown();
    logger_shutdown();
    window_shutdown(&g_app_state.window_state);
    
    g_app_state.is_running = false;
    return true;
}

b8 application_on_event(u16 code, void *sender, void *listener,
                        event_context event) {
    return true;
}