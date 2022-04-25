/* date = April 25th 2022 7:18 am */

#ifndef INPUT_H
#define INPUT_H

enum MouseButton
{
    Button_Left = SDL_BUTTON_LEFT,
    Button_Middle = SDL_BUTTON_LEFT,
    Button_Right = SDL_BUTTON_LEFT,
    
    Button_Total
};

enum KeyCode
{
    KeyCode_Unknown = -1,
    
    Key_0 = SDLK_0,
    Key_1 = SDLK_1,
    Key_2 = SDLK_2,
    Key_3 = SDLK_3,
    Key_4 = SDLK_4,
    Key_5 = SDLK_5,
    Key_6 = SDLK_6,
    Key_7 = SDLK_7,
    Key_8 = SDLK_8,
    Key_9 = SDLK_9,
    
    Key_A = SDLK_a,
    Key_B = SDLK_b,
    Key_C = SDLK_c,
    Key_D = SDLK_d,
    Key_E = SDLK_e,
    Key_F = SDLK_f,
    Key_G = SDLK_g,
    Key_H = SDLK_h,
    Key_I = SDLK_i,
    Key_J = SDLK_j,
    Key_K = SDLK_k,
    Key_L = SDLK_l,
    Key_M = SDLK_m,
    Key_N = SDLK_n,
    Key_O = SDLK_o,
    Key_P = SDLK_p,
    Key_Q = SDLK_q,
    Key_R = SDLK_r,
    Key_S = SDLK_s,
    Key_T = SDLK_t,
    Key_U = SDLK_u,
    Key_V = SDLK_v,
    Key_W = SDLK_w,
    Key_X = SDLK_x,
    Key_Y = SDLK_y,
    Key_Z = SDLK_z,
    
    Key_Total
};

global_variable u32 last_keyboard[256] = {};
global_variable u32 keyboard[256] = {};

void input_update(u32 code)
{
}

// Keyboard
bool is_key_down(const KeyCode code)
{
    return keyboard[code];
}

bool is_key_up(const KeyCode code)
{
    return !keyboard[code] && last_keyboard[code];
}

// MouseButton
bool is_mouse_down(const MouseButton button)
{
    return true;
}

bool is_mouse_up(const MouseButton button)
{
    return true;
}

#endif //INPUT_H
