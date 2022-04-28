#ifndef ALEX_MOUSE_H
#define ALEX_MOUSE_H

#include "alex.h"

typedef enum 
{
    MOUSE_BUTTON_LEFT    = 0,
    MOUSE_BUTTON_RIGHT   = 1,
    MOUSE_BUTTON_MIDDLE  = 2
} MouseButton;

typedef struct Mouse
{
	b8 current_buttons[3];
	b8 previous_buttons[3];
    b8 pressed_buttons[3];
} Mouse;

void mouse_init(Mouse *mouse);

void mouse_pre_poll(Mouse *mouse);
void mouse_post_poll(Mouse *mouse);

void mouse_reset(Mouse *mouse);

void mouse_on_button_down(Mouse *mouse, const u8 button);
void mouse_on_button_up(Mouse *mouse, const u8 button);

b8 mouse_is_down(const Mouse *mouse, const u8 button);
b8 mouse_is_pressed(const Mouse *mouse, const u8 button);
b8 mouse_is_released(const Mouse *mouse, const u8 button);

#endif
