#if ALEX_WIN32

#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "alex.cpp"

LRESULT CALLBACK win32_main_window_callback(HWND window, u32 msg, WPARAM w_param, LPARAM l_param);

bool win32_create_window();
bool win32_process_messages();
void win32_update_window(HDC device_contex, RECT *client_rect, i32 x, i32 y, i32 width, i32 height);
void win32_resize_dib_section(i32 width, i32 height);
void render_weird_gradient(i32 x_offset, i32 y_offset);

global_variable bool running;

global_variable const char* window_title = "AlexEngine";
global_variable HWND window;
global_variable HINSTANCE window_instance;

global_variable BITMAPINFO bitmap_info;
global_variable void *bitmap_memory;
global_variable i32 bitmap_width;
global_variable i32 bitmap_height;
global_variable i32 bytes_per_pixel = 4;

int CALLBACK
WinMain(HINSTANCE h_instance, HINSTANCE prev_instance, LPSTR cmd_line, int show_cmd)
{
    if (!win32_create_window())
    {
        return -1;
    }
    
    running  = true;
    while (running)
    {
        if (!win32_process_messages()) 
        {
            running  = false;
        }
        
        // Render
        local_variable i32 x_offset = 0;
        local_variable i32 y_offset = 0;
        
        render_weird_gradient(x_offset, y_offset);
        
        HDC device_context = GetDC(window);
        RECT client_rect;
        GetClientRect(window, &client_rect);
        i32 window_width = client_rect.right - client_rect.left;
        i32 window_height = client_rect.bottom - client_rect.top;
        
        win32_update_window(device_context, &client_rect, 0, 0, window_width, window_height);
        ReleaseDC(window, device_context);
        
        ++x_offset;
        
        Sleep(1);
    }
    
    return 0;
}

LRESULT CALLBACK 
win32_main_window_callback(HWND window, u32 msg, WPARAM w_param, LPARAM l_param) 
{
    switch (msg) 
    {
        case WM_SIZE:
        {
            RECT client_rect = {};
            GetClientRect(window, &client_rect);
            int width = client_rect.right - client_rect.left;
            int height = client_rect.bottom - client_rect.top;
            
            win32_resize_dib_section(width, height);
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT paint = {};
            HDC device_context = BeginPaint(window, &paint);
            int x = paint.rcPaint.left;
            int y = paint.rcPaint.top;
            int width = paint.rcPaint.right - paint.rcPaint.left;
            int height = paint.rcPaint.bottom - paint.rcPaint.top;
            
            RECT client_rect = {};
            GetClientRect(window, &client_rect);
            
            win32_update_window(device_context, &client_rect, x, y, width, height);
            EndPaint(window, &paint);
        } break;
        
        //case WM_ERASEBKGND: 
        //return 1;
        case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProcA(window, msg, w_param, l_param);
}

internal bool
win32_create_window() 
{
    window_instance = GetModuleHandle(0);
    
    // Class registration
    HICON h_icon = LoadIcon(window_instance, IDI_APPLICATION);
    WNDCLASS window_class;
    memset(&window_class, 0, sizeof(window_class));
    window_class.style = CS_DBLCLKS;
    window_class.lpfnWndProc = win32_main_window_callback;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = window_instance;
    window_class.hIcon = h_icon;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = 0;
    window_class.lpszClassName = "alex_window_class";
    
    if (!RegisterClassA(&window_class)) 
    {
        printf("[ERROR] RegisterClassA failed!");
        return false;
    }
    
    i32 pos_x = 0;
    i32 pos_y = 30;
    i32 width = 1280;
    i32 height = 720;
    
    i32 client_x = pos_x;
    i32 client_y = pos_y;
    i32 client_width = width;
    i32 client_height = height;
    
    i32 window_x = client_x;
    i32 window_y = client_y;
    i32 window_width = client_width;
    i32 window_height = client_height;
    
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
    
    window = CreateWindowEx(window_ex_style, window_class.lpszClassName, window_title,
                            window_style, window_x, window_y, window_width,
                            window_height, 0, 0, window_instance, 0);
    if (!window)
    {
        printf("[ERROR] CreateWindowEx failed!");
        return false;
    }
    
    ShowWindow(window, true);
    
    return true;
}

internal bool 
win32_process_messages()
{
    MSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) 
    {
        if (msg.message == WM_QUIT) 
        {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return true;
}

internal void 
win32_update_window(HDC device_contex, RECT *client_rect, i32 x, i32 y, i32 width, i32 height)
{
    i32 window_width = client_rect->right - client_rect->left;
    i32 window_height = client_rect->bottom - client_rect->top;
    
    StretchDIBits(device_contex,
                  0, 0, bitmap_width, bitmap_height,
                  0, 0, window_width, window_height,
                  bitmap_memory,
                  &bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
}

internal void 
win32_resize_dib_section(i32 width, i32 height)
{
    if (bitmap_memory)
    {
        VirtualFree(bitmap_memory, 0, MEM_RELEASE);
    }
    
    bitmap_width = width;
    bitmap_height = height;
    
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = bitmap_width;
    bitmap_info.bmiHeader.biHeight = -bitmap_height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;
    
    i32 bitmap_memory_size = (bitmap_width * bitmap_height) * bytes_per_pixel;
    bitmap_memory = VirtualAlloc(0, bitmap_memory_size, MEM_COMMIT, PAGE_READWRITE);
}

internal void 
render_weird_gradient(i32 x_offset, i32 y_offset)
{
    i32 width = bitmap_width;
    i32 height = bitmap_height;
    
    i32 pitch = width * bytes_per_pixel;
    u8 *row = (u8 *)bitmap_memory;
    for (i32 y = 0; y < bitmap_height; ++y)
    {
        u32 *pixel = (u32 *)row;
        for (i32 x = 0; x < bitmap_width; ++x)
        {
            u8 blue = x + x_offset;
            u8 green = y + y_offset;
            
            *pixel++ = (green << 8) | blue;
        }
        row += pitch;
    }
}

#endif // ALEX_WIN32