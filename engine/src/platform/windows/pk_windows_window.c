#include "core/pk_assert.h"
#include "core/pk_input.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"
#include "core/pk_window.h"

#if PK_PLATFORM_WINDOWS

// Windows
#include <windows.h>
#include <windowsx.h>

// Glad
#include <glad/glad.h>

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;    // Handle Window Device
    HDC hdc;      // Handle Device Context
    HGLRC hglrc;  // OpenGL Rendering Context
} internal_state;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param,
                                       LPARAM l_param);

b8 create_gl_context(internal_state *state);

internal b8 window_initialize(window_state *window, const char *title,
                              i32 pos_x, i32 pos_y, i32 width, i32 height) {
    window->internal_state = malloc(sizeof(internal_state));
    
    internal_state *state = (internal_state *)window->internal_state;
    state->h_instance = GetModuleHandleA(NULL);
    
    // Class registration
    HICON h_icon = LoadIcon(state->h_instance, IDI_APPLICATION);
    WNDCLASS wc;
    memory_set(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state->h_instance;
    wc.hIcon = h_icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "pekora_window_class";
    
    if (!RegisterClassA(&wc)) {
        ASSERT_MSG(false, "Window registration failed!");
        return false;
    }
    
    u32 client_x = pos_x;
    u32 client_y = pos_y;
    u32 client_width = width;
    u32 client_height = height;
    
    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;
    
    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;
    
    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;
    
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);
    
    window_x += border_rect.left;
    window_y += border_rect.top;
    
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;
    
    HWND hwnd = CreateWindowEx(window_ex_style, "pekora_window_class", title,
                               window_style, window_x, window_y, window_width,
                               window_height, 0, 0, state->h_instance, 0);
    
    if (!hwnd) {
        ASSERT_MSG(false, "Window creation failed!");
        return false;
    } else {
        state->hwnd = hwnd;
    }
    
    if (!create_gl_context(state)) {
        ASSERT_MSG(false, "create_gl_context failed!");
        return false;
    }
    
    // Initialize glad
    if (!gladLoadGL()) {
        ASSERT_MSG(false, "gladLoadGLLoader failed!");
        return false;
    }
    
    // Print OpenGL version
    LOG_DEBUG("[Engine] Current OpenGL Version: 3.3.0");
    LOG_DEBUG("[PC] OpenGL Version: %s", (char *)glGetString(GL_VERSION));
    LOG_DEBUG("[PC] OpenGL Shading Language Version: %s",
              (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    LOG_DEBUG("[PC] OpenGL Vendor: %s", (char *)glGetString(GL_VENDOR));
    LOG_DEBUG("[PC] OpenGL Renderer: %s", (char *)glGetString(GL_RENDERER));
    
    // Update Viewport
    glViewport(0, 0, window_width, window_height);
    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
    
    b32 should_acrivate = 1;
    i32 show_window_command_flags = should_acrivate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ShowWindow(state->hwnd, show_window_command_flags);
    
    return true;
}

b8 create_gl_context(internal_state *state) {
    state->h_instance = GetModuleHandleA(0);
    state->hdc = GetDC(state->hwnd);
    
    PIXELFORMATDESCRIPTOR pfd;
    memory_set(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixel_format = ChoosePixelFormat(state->hdc, &pfd);
    if (!pixel_format) {
        ASSERT_MSG(false, "ChoosePixelFormat failed!");
        return false;
    }
    
    BOOL bResult = SetPixelFormat(state->hdc, pixel_format, &pfd);
    if (!bResult) {
        ASSERT_MSG(false, "SetPixelFormat failed!");
        return false;
    }
    
    state->hglrc = wglCreateContext(state->hdc);
    wglMakeCurrent(state->hdc, state->hglrc);
    
    return true;
}

internal b8 window_shutdown(window_state *window) {
    internal_state *state = (internal_state *)window->internal_state;
    if (state->hwnd) {
        if (!DestroyWindow(state->hwnd)) {
            LOG_ERROR("DestroyWindow failed.");
            return false;
        }
        state->hwnd = 0;
    }
    return true;
}

internal b8 window_poll_message() {
    b8 b_ret = 0;
    MSG msg;
    while ((b_ret = PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) != 0) &&
           b_ret != -1) {
        if (msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return true;
}

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param,
                                       LPARAM l_param) {
    switch (msg) {
        case WM_ERASEBKGND:
        return 1;
        case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
        case WM_DESTROY:
        return 0;
        case WM_SIZE:
        break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            keys key = (u16)w_param;
            input_process_key(key, pressed);
        } break;
        case WM_MOUSEMOVE: {
            i32 x = GET_X_LPARAM(l_param);
            i32 y = GET_Y_LPARAM(l_param);
            input_process_mouse_move(x, y);
        } break;
        case WM_MOUSEWHEEL: {
            i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if (z_delta != 0) {
                z_delta = (z_delta < 0) ? -1 : 1;
                input_process_mouse_wheel((i8)z_delta);
            }
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            b8 pressed = (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                          msg == WM_MBUTTONDOWN);
            buttons button = -1;
            switch (msg) {
                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                button = BUTTON_LEFT;
                break;
                case WM_MBUTTONDOWN:
                case WM_MBUTTONUP:
                button = BUTTON_MIDDLE;
                break;
                case WM_RBUTTONDOWN:
                case WM_RBUTTONUP:
                button = BUTTON_RIGHT;
                break;
            }
            input_process_button(button, pressed);
        } break;
    }
    
    // LOG_DEBUG("MSG: 0x%X, W_PARAM: %i", msg, (u16)w_param);
    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif  // PLATFORM_WINDOWS