#include "core/pk_input.h"

#include "core/pk_assert.h"
#include "core/pk_event.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"

typedef struct keyboard_state
{
    b8 keys[256];
} keyboard_state;

typedef struct mouse_state
{
    i32 x;
    i32 y;
    b8 buttons[BUTTON_MAX_BUTTONS];
} mouse_state;

typedef struct input_state
{
    keyboard_state keyboard_current;
    keyboard_state keyboard_previous;
    mouse_state mouse_current;
    mouse_state mouse_previous;
} input_state;

global b8 g_initialized = false;
global input_state g_state = {};

internal void
input_initialize ()
{
    g_initialized = true;
}

internal void
input_shutdown ()
{
    g_initialized = false;
}

internal void
input_update (f64 delta_time)
{
    memory_copy (&g_state.keyboard_previous, &g_state.keyboard_current,
                 sizeof (keyboard_state));
    memory_copy (&g_state.mouse_previous, &g_state.mouse_current,
                 sizeof (mouse_state));
}

internal void
input_process_key (keys key, b8 pressed)
{
    if (g_state.keyboard_current.keys[key] != pressed)
    {
        g_state.keyboard_current.keys[key] = pressed;
        
        event_context context = {};
        context.data.u32[0] = key;
        event_fire (pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED,
                    NULL, context);
    }
}

internal void
input_process_button (buttons button, b8 pressed)
{
    if (g_state.keyboard_current.keys[button] != pressed)
    {
        g_state.keyboard_current.keys[button] = pressed;
        
        event_context context = {};
        context.data.u8[0] = button;
        event_fire (pressed ? EVENT_CODE_BUTTON_PRESSED
                    : EVENT_CODE_BUTTON_RELEASED,
                    NULL, context);
    }
}

internal void
input_process_mouse_move (i32 x, i32 y)
{
    if (g_state.mouse_current.x != x || g_state.mouse_current.y != y)
    {
        g_state.mouse_current.x = x;
        g_state.mouse_current.y = y;
        
        event_context context = {};
        context.data.i32[0] = x;
        context.data.i32[1] = y;
        event_fire (EVENT_CODE_MOUSE_MOVED, NULL, context);
    }
}

internal void
input_process_mouse_wheel (i8 z_delta)
{
    event_context context = {};
    context.data.i8[0] = z_delta;
    event_fire (EVENT_CODE_MOUSE_WHEEL, NULL, context);
}

void
input_get_mouse_position (i32 *x, i32 *y)
{
    *x = g_state.mouse_current.x;
    *y = g_state.mouse_current.y;
}

void
input_get_previous_mouse_position (i32 *x, i32 *y)
{
    *x = g_state.mouse_previous.x;
    *y = g_state.mouse_previous.y;
}

// keyboard input
b8
input_is_key_down (keys key)
{
    return g_state.keyboard_current.keys[key] == true;
}

b8
input_is_key_up (keys key)
{
    return g_state.keyboard_current.keys[key] == false;
}

b8
input_was_key_down (keys key)
{
    return g_state.keyboard_previous.keys[key] == true;
}

b8
input_was_key_up (keys key)
{
    return g_state.keyboard_previous.keys[key] == false;
}

// mouse input
b8
input_is_button_down (buttons button)
{
    return g_state.mouse_current.buttons[button] == true;
}

b8
input_is_button_up (buttons button)
{
    return g_state.mouse_current.buttons[button] == false;
}

b8
input_was_button_down (buttons button)
{
    return g_state.mouse_previous.buttons[button] == true;
}

b8
input_was_button_up (buttons button)
{
    return g_state.mouse_previous.buttons[button] == false;
}
