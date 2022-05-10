#ifndef ALEX_INPUT_H
#define ALEX_INPUT_H

enum Input_Event_Type
{
    InputEventType_None = 0,
    InputEventType_MouseButton,
    InputEventType_MouseMoved,
    InputEventType_MouseWheel,
    InputEventType_Key,
    InputEventType_Text,
    InputEventType_Count
};

enum Input_Source
{
    InputSource_None = 0,
    InputSource_Mouse,
    InputSource_Keyboard,
    InputSource_Count
};

struct Input_Event
{
    Input_Event_Type type;
    Input_Source source;
    
    struct
    {
        i8 button;
        b8 down;
    } button;
    
    struct
    {
        i32 key;
        b8 down;
    } key;
    
    struct
    {
        u8 c;
    } text;
    
    v2 mouse_position;
    i32 mouse_wheel;
};


enum Mouse_Button 
{
    MouseButton_Left = 0,
    MouseButton_Middle = 1,
    MouseButton_Right = 2,
    MouseButton_Unknown = -1
};

enum Key_Code
{
    KeyCode_0 = 0,
    KeyCode_1,
    KeyCode_2,
    KeyCode_3,
    KeyCode_4,
    KeyCode_5,
    KeyCode_6,
    KeyCode_7,
    KeyCode_8,
    KeyCode_9,
    
    KeyCode_F1,
    KeyCode_F2,
    KeyCode_F3,
    KeyCode_F4,
    KeyCode_F5,
    KeyCode_F6,
    KeyCode_F7,
    KeyCode_F8,
    KeyCode_F9,
    KeyCode_F10,
    KeyCode_F11,
    KeyCode_F12,
    
    KeyCode_A,
    KeyCode_B,
    KeyCode_C,
    KeyCode_D,
    KeyCode_E,
    KeyCode_F,
    KeyCode_G,
    KeyCode_H,
    KeyCode_I,
    KeyCode_J,
    KeyCode_K,
    KeyCode_L,
    KeyCode_M,
    KeyCode_N,
    KeyCode_O,
    KeyCode_P,
    KeyCode_Q,
    KeyCode_R,
    KeyCode_S,
    KeyCode_T,
    KeyCode_U,
    KeyCode_V,
    KeyCode_W,
    KeyCode_X,
    KeyCode_Y,
    KeyCode_Z,
    KeyCode_Unknown = -1,
};

struct Input
{
    b8 mouse_down[3];
    b8 mouse_prev_down[3];
    b8 mouse_pressed[3];
    b8 mouse_released[3];
    
    b8 key_down[256];
    b8 key_prev_down[256];
    b8 key_pressed[256];
    b8 key_released[256];
    
    v2 mouse_position;
    v2 mouse_prev_position;
    v2 mouse_delta;
    i32 mouse_wheel;
    
    Input_Event events;
};

internal void input_init(Input *input);

// Events
internal void input_add_key_event(Input *input, const Key_Code key, const b8 down);  
internal void input_add_character_event(Input *input, const u8 c);  

internal void input_add_mouse_button_event(Input *input, const Mouse_Button button, const b8 down);  
internal void input_add_mouse_position_event(Input *input, const v2 position);  
internal void input_add_mouse_wheel_event(Input *input, const i32 wheel);  

internal void input_update(Input *input);
internal void input_reset(Input *input);

// Keyboard
internal b8 input_is_key_down(const Input *input, const Key_Code key);
internal b8 input_is_key_pressed(const Input *input, const Key_Code key);
internal b8 input_is_key_released(const Input *input, const Key_Code key);

// Mouse
internal b8 input_is_mouse_down(const Input *input, const Mouse_Button button);
internal b8 input_is_mouse_pressed(const Input *input, const Mouse_Button button);
internal b8 input_is_mouse_released(const Input *input, const Mouse_Button button);

internal v2 input_get_mouse_position(const Input *input);
internal v2 input_get_mouse_delta(const Input *input);
internal i32 input_get_mouse_wheel(const Input *input);

#endif // ALEX_INPUT_H
