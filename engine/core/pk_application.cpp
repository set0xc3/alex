#include "core/pk_application.h"

#include "core/pk_assert.h"
#include "core/pk_clock.h"
#include "core/pk_input.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "core/pk_time.h"
#include "core/pk_window.h"
#include "pk_common.h"
#include "pk_game_types.h"

struct application_state 
{
    bool is_running;
    bool is_suspended;
    i32 width;
    i32 height;
    f64 last_time;
    Clock clock;
    Game *game;
    Window_State window;
};

global bool g_initialized = false;
global application_state app = {};

bool 
application_create(Game *game) 
{
    if (g_initialized) 
    {
        LOG_ERROR("application_create failed.");
        return false;
    }
    
    app.game = game;
    
    // Initialize sybsystems
    input_initialize();
    logger_initialize();
    
    // TODO(parsecffo): Remove this
    LOG_FATAL("Message: %f", 3.14f);
    LOG_ERROR("Message: %f", 3.14f);
    LOG_WARN("Message: %f", 3.14f);
    LOG_INFO("Message: %f", 3.14f);
    LOG_DEBUG("Message: %f", 3.14f);
    LOG_TRACE("Message: %f\n", 3.14f);
    
    app.is_running = true;
    app.is_suspended = false;
    
    if (!window_initialize(&app.window, game->app.name,
                           game->app.pos_x, game->app.pos_y,
                           game->app.width, game->app.height)) 
    {
        LOG_ERROR("window_initialize failed.");
        return false;
    }
    
    // Initialize the game
    if (!app.game->initialize()) 
    {
        LOG_FATAL("Game failed to initialize.");
        return false;
    }
    
    app.game->on_resize(app.width, app.height);
    
    g_initialized = true;
    return true;
}

bool 
application_run() 
{
    // Clock
    clock_start(&app.clock);
    clock_update(&app.clock);
    app.last_time = app.clock.elapsed;
    
    local f64 running_time = 0;
    local u8 frame_count = 0;
    local f64 target_frame_seconds = 1.0f / 144;
    
    LOG_INFO(get_memory_usage_str());
    
    while (app.is_running) 
    {
        // Update clock and get delta time
        clock_update(&app.clock);
        f64 current_time = app.clock.elapsed;
        f64 delta_time = (current_time - app.last_time);
        f64 frame_start_time = get_absolute_time();
        
        if (!window_poll_message()) 
        {
            app.is_running = false;
        }
        
        if (!app.is_suspended) 
        {
            input_update(delta_time);
            app.game->update(delta_time);
            app.game->render(delta_time);
            window_update(&app.window);
        }
        
        // Figure out how long frame took and, if below
        f64 frame_end_time = get_absolute_time();
        f64 frame_elapsed_time = frame_end_time - frame_start_time;
        running_time += frame_elapsed_time;
        f64 remaining_seconds = target_frame_seconds - frame_elapsed_time;
        if (remaining_seconds > 0) 
        {
            u64 remaining_ms = (remaining_seconds * 1000);
            // If there if time left, give if back to the OS
            bool limit_frames = true;
            if (remaining_ms > 0 && limit_frames) 
            {
                wait_time(remaining_ms - 1);
            }
            frame_count++;
        }
        
        // Update last time
        app.last_time = current_time;
    }
    
    clock_stop(&app.clock);
    
    // Shutdown subsystems
    
    input_shutdown();
    logger_shutdown();
    window_shutdown(&app.window);
    
    app.is_running = false;
    return true;
}
