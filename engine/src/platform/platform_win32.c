#include "core/logger.h"
#include "platform.h"

#if PLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 platform_startup(
    platform_state *platform,
    const char *title,
    i32 pos_x,
    i32 pos_y,
    i32 width,
    i32 height) {
    platform->internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)platform->internal_state;

    state->h_instance = GetModuleHandleA(0);

    HICON h_icon = LoadIcon(state->h_instance, IDI_APPLICATION);
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
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
        LOG_ERROR("Window registration failed.");
        return false;
    }

    // Create window
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

    HWND handle = CreateWindowEx(
        window_ex_style, "pekora_window_class", title,
        window_style, window_x, window_y, window_width, window_height,
        0, 0, state->h_instance, 0);

    if (handle == NULL) {
        LOG_ERROR("Window creation failed.");
        return false;
    } else {
        state->hwnd = handle;
    }

    b32 should_acrivate = 1;
    i32 show_window_command_flags = should_acrivate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ShowWindow(state->hwnd, show_window_command_flags);

    return true;
}

b8 platform_shutdown(platform_state *platform) {
    internal_state *state = (internal_state *)platform->internal_state;
    if (state->hwnd) {
        if (!DestroyWindow(state->hwnd)) {
            LOG_ERROR("DestroyWindow failed.");
            return false;
        }
        state->hwnd = 0;
    }
    return true;
}

b8 platform_poll_message(platform_state *platform) {
    b8 b_ret = 0;
    MSG msg;
    while ((b_ret = PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) != 0) && b_ret != -1) {
        if (msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return true;
}

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
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
            // Key pressed/release
            // b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            // TODO(parsecffo): input processing.
        } break;
        case WM_MOUSEMOVE: {
            // Mouse move
            // i32 x_pos = GET_X_LPARAM(l_param);
            // i32 y_pos = GET_Y_LPARAM(l_param);
            // TODO(parsecffo): input processing.
        } break;
        case WM_MOUSEWHEEL: {
            i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if (z_delta != 0) {
                z_delta = (z_delta < 0) ? -1 : 1;
                // TODO(parsecffo): input processing.
            }
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            // b8 pressed = (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN);
            // TODO(parsecffo): input processing.
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif  // PLATFORM_WINDOWS