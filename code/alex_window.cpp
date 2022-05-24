#include "alex_window.h"

internal void 
glfw_error_callback(i32 error, const char* description)
{
    fprintf(stderr, "[GLFW] Error %d: %s\n", error, description);
}

internal b8 
create_window(const Window_Data *wd, Window *window)
{
    ZERO_STRUCT(window);
    
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return false;
    }
    
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    
    // Create window with graphics context
    window->glfw_window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", 0, 0);
    if (!window->glfw_window)
    {
        return false;
    }
    
    glfwMakeContextCurrent(window->glfw_window);
    glfwSwapInterval(1);
    
    return true;
}

internal void 
destroy_window(Window *window)
{
    glfwDestroyWindow(window->glfw_window);
    glfwTerminate();
}

internal void 
window_display(Window *window)
{
    glfwSwapBuffers(window->glfw_window);
}

internal b8 
window_handle_event(Window *window)
{
    glfwPollEvents();
    
    if (glfwWindowShouldClose(window->glfw_window))
        return false;
    
    return true;
}

internal void 
window_set_visible(Window *window, const b8 visible)
{
}

internal void 
window_set_vsync(Window *window, const b8 interval)
{
}