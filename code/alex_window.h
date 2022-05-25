#ifndef ALEX_WINDOW_H
#define ALEX_WINDOW_H

struct GLFWwindow;

struct Window_Data
{
    i32 pos_x; 
    i32 pos_y;
    i32 width;
    i32 height;
    char title[256];
};

struct Window
{
    GLFWwindow *glfw_window;
};

internal b8 create_window(const Window_Data *wd, Window *window);
internal void destroy_window(Window *window);
internal void window_display(Window *window);
internal b8 window_handle_event(Window *window);

internal void window_set_visible(Window *window, const b8 visible);
internal void window_set_vsync(Window *window, const b8 interval);

#endif // ALEX_WINDOW_H