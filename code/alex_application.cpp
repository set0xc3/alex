#include "alex_application.h"

internal void 
create_application()
{
    ZERO_STRUCT(&app);
    
    // Test Log
#if 1
    LOG_INFO("PI: %f", PI);
    LOG_WARN("PI: %f", PI);
    LOG_DEBUG("PI: %f", PI);
    LOG_TRACE("PI: %f", PI);
    LOG_ERROR("PI: %f", PI);
    LOG_FATAL("PI: %f\n", PI);
#endif
    
    Window_Data wd;
    create_window(&wd, &app.window);
    
    app.running = true;
    while (app.running)
    {
        if (!window_handle_event(&app.window))
            app.running = false;
        
        window_display(&app.window);
    }
    
    destroy_window(&app.window);
}