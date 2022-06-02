/* date = June 2nd 2022 6:26 pm */

#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

struct renderer_context
{
};

internal void startup_renderer(renderer_context *context);
internal void shutdown_renderer(renderer_context *context);

internal b8 renderer_handle_input(renderer_context *context);

internal void renderer_begin(renderer_context *context);
internal void renderer_end(renderer_context *context);

internal void renderer_flush(renderer_context *context);
internal void renderer_draw(renderer_context *context);

#endif //ALEX_RENDERER_H
