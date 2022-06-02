/* date = June 2nd 2022 1:10 pm */

#ifndef ALEX_WINDOW_H
#define ALEX_WINDOW_H

struct window_context
{
    void *internal_data;
};

internal void create_window(window_context *context);
internal void destroy_window(window_context *context);

internal void window_update(window_context *context);
internal b8 window_handle_input(window_context *context);

internal void window_set_name_title(window_context *context, const char *title);

#endif //ALEX_WINDOW_H
