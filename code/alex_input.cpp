#include "alex_input.h"
#include "alex_logger.h"

void Input::add_key_event(const Key_Code key, const b8 down)
{
    key_down[key] = down;
}

void Input::add_character_event(u8 c)
{
}

void Input::add_mouse_button_event(const Mouse_Button button, const b8 down)
{
    mouse_down[button] = down;
}

void Input::add_mouse_position_event(const f32 x, const f32 y)
{
    memcpy(mouse_prev_position, mouse_position, sizeof(mouse_prev_position));
    mouse_position[0] = x;
    mouse_position[1] = y;
    
    // Calc delta
    mouse_delta[0] = mouse_position[0] - mouse_prev_position[0];
    mouse_delta[1] = mouse_position[1] - mouse_prev_position[1];
}

void Input::add_mouse_wheel_event(const f32 x, const f32 y)
{
    mouse_wheel[0] = x;
    mouse_wheel[1] = y;
}

void Input::update()
{
}

void Input::reset()
{
    memset(mouse_wheel, 0, sizeof(mouse_wheel));
    memset(mouse_delta, 0, sizeof(mouse_delta));
}

b8 Input::is_key_down(const Key_Code key)
{
    return key_down[key];
}

b8 Input::is_key_pressed(const Key_Code key)
{
    return key_pressed[key];
}

b8 Input::is_key_released(const Key_Code key)
{
    return key_released[key];
}

b8 Input::is_mouse_down(const Mouse_Button button)
{
    return mouse_down[button];
}

b8 Input::is_mouse_pressed(const Mouse_Button button)
{
    return mouse_pressed[button];
}

b8 Input::is_mouse_released(const Mouse_Button button)
{
    return mouse_released[button];
}

void Input::get_mouse_position()
{
}

void Input::get_mouse_delta()
{
}

void Input::get_mouse_wheel()
{
}