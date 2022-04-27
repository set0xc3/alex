#ifndef ALEX_MOUSE_H
#define ALEX_MOUSE_H

#include "alex.h"

typedef struct
{
	b8 current_buttons[3];
	b8 previous_buttons[3];
    b8 pressed_buttons[3];
} Mouse_t;

void mouse_init(Mouse_t *mouse);

void mouse_pre_poll(Mouse_t *mouse);
void mouse_post_poll(Mouse_t *mouse);

void mouse_reset(Mouse_t *mouse);

void mouse_on_button_down(Mouse_t *mouse, const u8 button);
void mouse_on_button_up(Mouse_t *mouse, const u8 button);

b8 mouse_is_down(const Mouse_t *mouse, const u8 button);
b8 mouse_is_pressed(const Mouse_t *mouse, const u8 button);
b8 mouse_is_released(const Mouse_t *mouse, const u8 button);

#endif
