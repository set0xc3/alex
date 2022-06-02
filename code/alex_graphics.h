/* date = June 2nd 2022 6:26 pm */

#ifndef ALEX_GRAPHICS_H
#define ALEX_GRAPHICS_H

#include "alex_window.h"

struct graphics_context
{
    window_context window;
};

internal void startup_graphics(graphics_context *context);
internal void shutdown_graphics(graphics_context *context);

internal b8 graphics_handle_input(graphics_context *context);
internal void graphics_update(graphics_context *context);

#endif //ALEX_GRAPHICS_H
