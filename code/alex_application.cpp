#include "alex_application.h"
#include "alex_platform.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    
    // Create Window
    Window_Data wd;
    ZERO_STRUCT(&wd);
    sprintf(wd.title, "Engine");
    wd.pos_x = 0;
    wd.pos_y = 0;
    wd.width = 800;
    wd.height = 600;
    create_window(&wd, &app.window);
    
    // Create Renderer
    create_renderer(&app.renderer);
    renderer_set_viewport(0, 0, 800, 600);
    
    // Sandbox
    sandbox_init();
    
    app.running = true;
    while (app.running)
    {
        if (!window_handle_event())
        {
            app.running = false;
            
            LOG_INFO("Shutdown");
            break;
        }
        
        renderer_set_color(0.1f, 0.1f, 0.1f);
        
        sandbox_on_event();
        sandbox_on_update();
        sandbox_on_render();
        
        window_display(&app.window);
        
        //LOG_DEBUG("TEST");
        platform_delay(1000/60);
    }
}