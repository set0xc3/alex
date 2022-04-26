#ifndef ALEX_INPUT_H
#define ALEX_INPUT_H

#include "alex.h"

#include <vector>
#include <cstring>

namespace Alex
{
    namespace Input
    {
        enum MouseButton
        {
            MouseButton_Left = 0,
            MouseButton_Middle,
            MouseButton_Right,
            
            MouseButton_Count
        };
        
        enum Key
        {
            Key_0 = 0,
            Key_1 = 0,
            Key_2 = 0,
            Key_3 = 0,
            Key_4 = 0,
            Key_5 = 0,
            Key_6 = 0,
            Key_7 = 0,
            Key_8 = 0,
            Key_9 = 0,
            
            Key_A = 0,
            Key_B = 0,
            Key_C = 0,
            Key_D = 0,
            Key_E = 0,
            Key_F = 0,
            Key_G = 0,
            Key_H = 0,
            Key_I = 0,
            Key_J = 0,
            Key_K = 0,
            Key_L = 0,
            Key_M = 0,
            Key_N = 0,
            Key_O = 0,
            Key_P = 0,
            Key_Q = 0,
            Key_R = 0,
            Key_S = 0,
            Key_T = 0,
            Key_U = 0,
            Key_V = 0,
            Key_W = 0,
            Key_X = 0,
            Key_Y = 0,
            Key_Z = 0,
            
            Key_Count
        };
        
        struct KeyData
        {
            bool down;
        };
        
        enum InputEventType
        {
            InputEventType_None = 0,
            InputEventType_MouseButton,
            InputEventType_Key,
            
            InputEventType_Count
        };
        
        enum InputSource
        {
            InputSource_None = 0,
            InputSource_Mouse,
            InputSource_Keyboard,
            
            InputSource_Count
        };
        
        struct InputEventMouseButton { i32 button; bool down; };
        struct InputEventKey { Key key; bool down; };
        
        struct InputEvent
        {
            InputEventType type;
            InputSource source;
            union
            {
                InputEventKey key;
                InputEventMouseButton mouse_button;
            };
            
            InputEvent() { memset(this, 0, sizeof(*this)); }
        };
    }
}

#endif // ALEX_INPUT_H
