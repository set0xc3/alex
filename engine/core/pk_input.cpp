#include "core/pk_input.h"

#include "core/pk_assert.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"

struct Keyboard_State
{
    bool keys[256];
};

struct Mouse_State
{
    i32 x;
    i32 y;
    bool buttons[BUTTON_MAX_BUTTONS];
};

struct Input_State
{
    Keyboard_State keyboard_current;
    Keyboard_State keyboard_previous;
    Mouse_State mouse_current;
    Mouse_State mouse_previous;
};

global bool g_initialized = false;
global Input_State g_state = {};

internal void
input_initialize()
{
    g_initialized = true;
}

internal void
input_shutdown()
{
    g_initialized = false;
}

internal void
input_update(f64 delta_time)
{
    memory_copy (&g_state.keyboard_previous, &g_state.keyboard_current, sizeof (Keyboard_State));
    memory_copy (&g_state.mouse_previous, &g_state.mouse_current, sizeof (Mouse_State));
}

internal void
input_process_key(Keys key, bool pressed)
{
    if (g_state.keyboard_current.keys[key] != pressed)
    {
        g_state.keyboard_current.keys[key] = pressed;
    }
}

internal void
input_process_button(Buttons button, bool pressed)
{
    if (g_state.keyboard_current.keys[button] != pressed)
    {
        g_state.keyboard_current.keys[button] = pressed;
    }
}

internal void
input_process_mouse_move(i32 x, i32 y)
{
    if (g_state.mouse_current.x != x || g_state.mouse_current.y != y)
    {
        g_state.mouse_current.x = x;
        g_state.mouse_current.y = y;
    }
}

internal void
input_process_mouse_wheel(i8 z_delta)
{
}

void
input_get_mouse_position(i32 *x, i32 *y)
{
    *x = g_state.mouse_current.x;
    *y = g_state.mouse_current.y;
}

void
input_get_previous_mouse_position(i32 *x, i32 *y)
{
    *x = g_state.mouse_previous.x;
    *y = g_state.mouse_previous.y;
}

// keyboard input
bool
input_is_key_down(Keys key)
{
    return g_state.keyboard_current.keys[key] == true;
}

bool
input_is_key_up(Keys key)
{
    return g_state.keyboard_current.keys[key] == false;
}

bool
input_was_key_down(Keys key)
{
    return g_state.keyboard_previous.keys[key] == true;
}

bool
input_was_key_up(Keys key)
{
    return g_state.keyboard_previous.keys[key] == false;
}

// mouse input
bool
input_is_button_down(Buttons button)
{
    return g_state.mouse_current.buttons[button] == true;
}

bool
input_is_button_up(Buttons button)
{
    return g_state.mouse_current.buttons[button] == false;
}

bool
input_was_button_down(Buttons button)
{
    return g_state.mouse_previous.buttons[button] == true;
}

bool
input_was_button_up(Buttons button)
{
    return g_state.mouse_previous.buttons[button] == false;
}
