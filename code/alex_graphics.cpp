#include "alex_graphics.h"


internal void 
startup_graphics(graphics_context *context)
{
    create_window(&context->window);
}

internal void 
shutdown_graphics(graphics_context *context)
{
    destroy_window(&context->window);
}

internal b8 
graphics_handle_input(graphics_context *context)
{
    if (!window_handle_input(&context->window))
        return false;
    
    return true;
}

internal void 
graphics_update(graphics_context *context)
{
    window_update(&context->window);
}