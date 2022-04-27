#include "mouse.h"

#include <string.h>

void
mouse_init(Mouse_t *mouse)
{
    memset(mouse, 0, sizeof(*mouse));
}

void 
mouse_pre_poll(Mouse_t *mouse)
{
    memset(mouse->pressed_buttons, 0, sizeof(mouse->pressed_buttons));
    memcpy(mouse->previous_buttons, mouse->current_buttons, sizeof(mouse->previous_buttons));
}

void
mouse_post_poll(Mouse_t *mouse)
{
    for (i64 i = 0; i < 3; ++i)
    {
        if (mouse->current_buttons[i] && !mouse->previous_buttons[i])
        {
            mouse->pressed_buttons[i] = true;
        }
    }
}

void 
mouse_reset(Mouse_t *mouse)
{
    memset(mouse->current_buttons, 0, sizeof(mouse->current_buttons));
    memset(mouse->previous_buttons, 0, sizeof(mouse->previous_buttons));
    memset(mouse->pressed_buttons, 0, sizeof(mouse->pressed_buttons));
}

void 
mouse_on_button_down(Mouse_t *mouse, const u8 button)
{
    mouse->current_buttons[button] = true;
}

void
mouse_on_button_up(Mouse_t *mouse, const u8 button)
{
    mouse->current_buttons[button] = false;
}

b8 
mouse_is_down(const Mouse_t *mouse, const u8 button)
{
    return mouse->current_buttons[button];
}

b8
mouse_is_pressed(const Mouse_t *mouse, const u8 button)
{
    return mouse->pressed_buttons[button];
}

b8
mouse_is_released(const Mouse_t *mouse, const u8 button)
{
    return !mouse->current_buttons[button] && mouse->previous_buttons[button];
}