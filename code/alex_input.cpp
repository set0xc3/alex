#include "alex_input.h"

internal void 
input_init(Input_State *input)
{
    memset(input, 0, sizeof(*input));
}

internal void 
input_add_key_event(Input_State *input, const Key_Code key, const b8 down)
{
    Input_Event e = {};
    e.type        = InputEventType_Key;
    e.source      = InputSource_Keyboard;
    e.key.key     = key;
    e.key.down    = down;
    input->events = e;
}

internal void 
input_add_mouse_button_event(Input_State *input, const Mouse_Button button, const b8 down)
{
    Input_Event e   = {};
    e.type          = InputEventType_MouseButton;
    e.source        = InputSource_Mouse;
    e.button.button = button;
    e.button.down   = down;
    input->events   = e;
}

internal void 
input_add_character_event(Input_State *input, u8 c)
{
    Input_Event e = {};
    e.type        = InputEventType_Text;
    e.source      = InputSource_Keyboard;
    e.text.c      = c;
    input->events = e;
}

internal void 
input_update(Input_State *input)
{
    Input_Event *e = &input->events;
    
    if (e->button.button != MouseButton_Unknown &&
        e->type == InputEventType_MouseButton)
    {
        memcpy(&input->mouse_prev_down, &input->mouse_down, sizeof(input->mouse_down));
        
        input->mouse_down[e->button.button] = e->button.down;
        input->mouse_pressed[e->button.button] = input->mouse_down[e->button.button] && !input->mouse_prev_down[e->button.button];
        input->mouse_released[e->button.button] = !input->mouse_down[e->button.button] && input->mouse_prev_down[e->button.button];
    }
    else if (e->key.key != KeyCode_Unknown && 
             e->type == InputEventType_Key)
    {
        memcpy(&input->key_prev_down, &input->key_down, sizeof(input->key_down));
        
        input->key_down[e->key.key] = e->key.down;
        input->key_pressed[e->key.key] = input->key_down[e->key.key] && !input->key_prev_down[e->key.key];
        input->key_released[e->key.key] = !input->key_down[e->key.key] && input->key_prev_down[e->key.key];
    }
}

internal void 
input_reset(Input_State *input)
{
    memset(&input->mouse_pressed, 0, sizeof(*input->mouse_pressed));
    memset(&input->mouse_released, 0, sizeof(*input->mouse_released));
    
    memset(&input->key_pressed, 0, sizeof(*input->key_pressed));
    memset(&input->key_released, 0, sizeof(*input->key_released));
}

internal b8
input_is_key_down(const Input_State *input, const Key_Code key)
{
    return input->key_down[key];
}

internal b8
input_is_key_pressed(const Input_State *input, const Key_Code key)
{
    return input->key_pressed[key];
}

b8
input_is_key_released(const Input_State *input, const Key_Code key)
{
    return input->key_released[key];
}

b8
input_is_mouse_down(const Input_State *input, const Mouse_Button button)
{
    return input->mouse_down[button];
}

b8
input_is_mouse_pressed(const Input_State *input, const Mouse_Button button)
{
    return input->mouse_pressed[button];
}

b8
input_is_mouse_released(const Input_State *input, const Mouse_Button button)
{
    return input->mouse_released[button];
}