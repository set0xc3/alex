#include "alex_input.h"
#include "alex_logger.h"

internal void 
input_init(Input *input)
{
    memset(input, 0, sizeof(*input));
}

internal void 
input_add_key_event(Input *input, const Key_Code key, const b8 down)
{
    input->key_down[key] = down;
}

internal void 
input_add_character_event(Input *input, u8 c)
{
}

internal void 
input_add_mouse_button_event(Input *input, const Mouse_Button button, const b8 down)
{
    input->mouse_down[button] = down;
}

internal
void input_add_mouse_position_event(Input *input, const v2 position)
{
    input->mouse_prev_position = input->mouse_position;
    input->mouse_position = position;
    
    // Calc delta
    input->mouse_delta.x = input->mouse_position.x - input->mouse_prev_position.x;
    input->mouse_delta.y = input->mouse_position.y - input->mouse_prev_position.y;
}

internal
void input_add_mouse_wheel_event(Input *input, const i32 wheel)
{
    input->mouse_wheel = wheel;
}

internal void 
input_update(Input *input)
{
    //LOG_DEBUG("mouse:delta(%f,%f)", input->mouse_delta.x, input->mouse_delta.y);
    //LOG_DEBUG("mouse:wheel(%i)", input->mouse_wheel);
    
#if 0
    
    //memset(&input->mouse_pressed, 0, sizeof(input->mouse_pressed));
    //memset(&input->mouse_released, 0, sizeof(input->mouse_released));
    
    //memset(&input->key_pressed, 0, sizeof(input->key_pressed));
    //memset(&input->key_released, 0, sizeof(input->key_released));
    
    if (e->button.button != MouseButton_Unknown && e->type == InputEventType_MouseButton)
    {
        memcpy(&input->mouse_prev_down, &input->mouse_prev_down, sizeof(input->mouse_down));
        
        input->mouse_down[e->button.button] = e->button.down;
        input->mouse_pressed[e->button.button] = input->mouse_down[e->button.button] && !input->mouse_prev_down[e->button.button];
        input->mouse_released[e->button.button] = !input->mouse_down[e->button.button] && input->mouse_prev_down[e->button.button];
    }
    else if (e->key.key != KeyCode_Unknown && e->type == InputEventType_Key)
    {
        memcpy(&input->key_prev_down, &input->key_prev_down, sizeof(input->key_down));
        
        input->key_down[e->key.key] = e->key.down;
        input->key_pressed[e->key.key] = input->key_down[e->key.key] && !input->key_prev_down[e->key.key];
        input->key_released[e->key.key] = !input->key_down[e->key.key] && input->key_prev_down[e->key.key];
    }
    else if (e->type == InputEventType_MouseMoved)
    {
        //input->mouse_prev_position = input->mouse_position;
        //input->mouse_position = e->mouse_position;
    }
    else if (e->type == InputEventType_MouseWheel)
    {
        //input->mouse_wheel = e->mouse_wheel;
    }
    
    //memset(&input->event, 0, sizeof(input->event));
#endif
}

internal void input_reset(Input *input)
{
    input->mouse_wheel = 0;
    input->mouse_delta = {0};
}

internal b8
input_is_key_down(const Input *input, const Key_Code key)
{
    return input->key_down[key];
}

internal b8
input_is_key_pressed(const Input *input, const Key_Code key)
{
    return input->key_pressed[key];
}

b8
input_is_key_released(const Input *input, const Key_Code key)
{
    return input->key_released[key];
}

b8
input_is_mouse_down(const Input *input, const Mouse_Button button)
{
    return input->mouse_down[button];
}

b8
input_is_mouse_pressed(const Input *input, const Mouse_Button button)
{
    return input->mouse_pressed[button];
}

b8
input_is_mouse_released(const Input *input, const Mouse_Button button)
{
    return input->mouse_released[button];
}

internal
v2 input_get_mouse_position(const Input *input)
{
    return input->mouse_position;
}

internal
v2 input_get_mouse_delta(const Input *input)
{
    return input->mouse_delta;
}

internal
i32 input_get_mouse_wheel(const Input *input)
{
    return input->mouse_wheel;
}