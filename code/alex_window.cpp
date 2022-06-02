#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include "alex_window.h"
#include "alex_logger.h"

struct _internal_data
{
    Window window;
    Display *display;
    XVisualInfo *visual;
    GLXContext gl_context;
};

internal void 
create_window(window_context *win)
{
    _internal_data *in = 0;
    in = (_internal_data*)malloc(sizeof(_internal_data));
    ZERO_MEMORY(in);
    win->internal_data = in;
    
    in->display = XOpenDisplay(0);
    if (!in->display)
    {
        // TODO(alex): debug
    }
    
    i32 nitems_return[5] =
    {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 
        24,
        GLX_DOUBLEBUFFER,
        0
    };
    in->visual = glXChooseVisual(in->display, 0, nitems_return);
    if (!in->visual) 
    {
        // TODO(alex): debug
    }
    
    in->gl_context = glXCreateContext(in->display, in->visual, 0, true);
    if (!in->gl_context) 
    {
        // TODO(alex): debug
    }
    
    i32 screen = DefaultScreen(in->display);
    u32 black = BlackPixel(in->display, screen);
    u32 white = WhitePixel(in->display, screen);
    
    in->window = XCreateSimpleWindow(in->display, 
                                     RootWindow(in->display, screen), 
                                     0, 0, 
                                     1280, 720, 
                                     5, 
                                     black, white);
    
    XStoreName(in->display, in->window, "AlexEngine");
    
    glXMakeCurrent(in->display, in->window, in->gl_context);
    
    u64 input_mask = ExposureMask|ButtonPressMask|KeyPressMask;
    XSelectInput(in->display, in->window, input_mask);
    
    XMapWindow(in->display, in->window);
	XFlush(in->display);
    
    XClearWindow(in->display, in->window);
	XMapRaised(in->display, in->window);
    
    // Process window close event in X11 event loop for(;;)
	Atom wnd_del = XInternAtom(in->display, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(in->display, in->window, &wnd_del, 1);
}

internal void 
destroy_window(window_context *win)
{
    _internal_data* in = (_internal_data*)win->internal_data;
    
    glXDestroyContext(in->display, in->gl_context);
    XFree(in->visual);
	XDestroyWindow(in->display, in->window);
	XCloseDisplay(in->display);	
}

internal void 
window_update(window_context *win)
{
    _internal_data* in = (_internal_data*)win->internal_data;
    
    glViewport(0, 0, 1280, 720);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    
    glXSwapBuffers(in->display, in->window);
}

internal b8 
window_handle_input(window_context *win)
{
    _internal_data* in = (_internal_data*)win->internal_data;
    while (XPending(in->display) > 0) 
    {
        XEvent event;
        XNextEvent(in->display, &event);
        
        if (event.type == ClientMessage)
        {
            LOG_DEBUG(" [Event] User closed window");
            return false;
        }
    }
    
    return true;
}

internal void 
window_set_name_title(window_context *win, const char *title)
{
    _internal_data* in = (_internal_data*)win->internal_data;
    XStoreName(in->display, in->window, title);
}