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
    
    app.running = true;
    while (app.running)
    {
        if (!window_handle_event())
        {
            app.running = false;
            
            LOG_INFO("Shutdown");
            break;
        }
        
        renderer_set_color(1.0f, 0.0f, 1.0f);
        
        // Update Camera
        {
            glUseProgram(app.renderer.shader.id);
            
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
            int projection_loc = glGetUniformLocation(app.renderer.shader.id, "u_projection");
            glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
            
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f)); 
            int view_loc = glGetUniformLocation(app.renderer.shader.id, "u_view");
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
            
            glUseProgram(0);
        }
        
        f32 p0[] = { 0.0f, 0.0f, 0.0f };
        f32 p1[] = { 10.0f, 0.0f, 0.0f };
        //renderer_draw_line(&app.renderer, p0, p1);
        
        renderer_draw_rect(&app.renderer, 0.0f, 0.0f, 10.0f, 10.0f);
        renderer_draw_fill_rect(&app.renderer, 1.0f, 1.0f, 10.0f, 10.0f);
        
        window_display(&app.window);
        
        //LOG_DEBUG("TEST");
        platform_delay(1000/16);
    }
}