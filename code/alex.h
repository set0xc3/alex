#ifndef ALEX_H
#define ALEX_H

/* Index of this file:
     
[SECTION] Headers
      [SECTION] Defines
[SECTION] Logger
[SECTION] Input
 [SECTION] Window

*/

/* TODO:

# Core:
 - Logger
- Time
- String
- Dynamic Arrays
- Memory
- Jobs
- Threads
 - Collision

# Systems:
- Input
- Event
- Audio
- Network
- Graphics
- Resources
- IMGUI/GUI
- Physics
 - Profiler
- AI

# Tools:
- Sandbox
- Editor

*/

//-----------------------------------------------
// [SECTION] Headers
//-----------------------------------------------

// Standard headers
#include <stdint.h> 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//-----------------------------------------------
// [SECTION] Defines
//-----------------------------------------------

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

// Bool
typedef uint8_t b8;

#define true 1
#define false 0

#define internal static
#define local_variable static
#define global_variable static

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define PI 3.14159f

//-----------------------------------------------
// [SECTION] Logger
//-----------------------------------------------

typedef enum
{
    LogType_Info,
    LogType_Debug,
    LogType_Warn,
    LogType_Error,
    LogType_Fatal,
    
} LogType;

void logger_init();
void logger_print(const LogType type, const char *fmt, ...);

#define LOG_INFO(fmt, ...)  logger_print (LogType_Info, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...)  logger_print (LogType_Warn, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) logger_print (LogType_Debug, fmt, __VA_ARGS__)
#define LOG_TRACE(fmt, ...) logger_print (LogType_Trace, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) logger_print (LogType_Error, fmt, __VA_ARGS__)
#define LOG_FATAL(fmt, ...) logger_print (LogType_Fatal, fmt, __VA_ARGS__)

//-----------------------------------------------
// [SECTION] Input
//-----------------------------------------------

typedef enum
{
    InputEventType_None = 0,
    InputEventType_MouseButton,
    InputEventType_Key,
    InputEventType_Text,
    InputEventType_Count
        
} InputEventType;

typedef enum
{
    InputSource_None = 0,
    InputSource_Mouse,
    InputSource_Keyboard,
    InputSource_Count
        
} InputSource;

typedef struct
{
    InputEventType type;
    InputSource source;
    
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
    
} InputEvent;


typedef enum 
{
    MouseButton_Left = 0,
    MouseButton_Middle = 1,
    MouseButton_Right = 2,
    
    MouseButton_Unknown = -1
        
} MouseButton;

typedef enum
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
    
} KeyCode;

typedef struct
{
    b8 mouse_down[3];
    b8 mouse_prev_down[3];
    b8 mouse_pressed[3];
    b8 mouse_released[3];
    
    b8 key_down[256];
    b8 key_prev_down[256];
    b8 key_pressed[256];
    b8 key_released[256];
    
    InputEvent events;
    
} InputContext;

void input_init (InputContext *input);

// Events
void input_add_key_event          (InputContext *input, const KeyCode key, const b8 down);  
void input_add_mouse_button_event (InputContext *input, const MouseButton button, const b8 down);  
void input_add_character_event    (InputContext *input, const u8 c);  

void input_update (InputContext *input);
void input_reset  (InputContext *input);

// Keyboard
b8 input_is_key_down     (const InputContext *input, const KeyCode key);
b8 input_is_key_pressed  (const InputContext *input, const KeyCode key);
b8 input_is_key_released (const InputContext *input, const KeyCode key);

// Mouse
b8 input_is_mouse_down     (const InputContext *input, const MouseButton button);
b8 input_is_mouse_pressed  (const InputContext *input, const MouseButton button);
b8 input_is_mouse_released (const InputContext *input, const MouseButton button);

//-----------------------------------------------
// [SECTION] Window
//-----------------------------------------------

typedef struct
{
    i32 x;
    i32 y;
    i32 width;
    i32 height;
    u32 flags;
    char *title;
    
} WindowData;

typedef struct
{
    SDL_Window *window;
    SDL_GLContext gl_context;
    
} WindowContext;

b8 window_init       (WindowContext *context);
void window_update   (WindowContext *context);
b8 window_event_poll (InputContext *context);

#endif // ALEX_H