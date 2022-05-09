#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_renderer.h"
#include "alex_shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

struct Application
{
    b8 running;
    
    Input input;
    Window window;
    Renderer renderer;
};

int 
main(void)
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    // Load Modules
    logger_init();
    input_init(&app.input);
    window_init(&app.window);
    renderer_init(&app.renderer);
    
    // Create Shaders
    local_variable Shader shader = 
        shader_create("assets/shaders/flat_color.vs", 
                      "assets/shaders/flat_color.fs");
    
    // Create Entity
    local_variable Entity entity;
    memset(&entity, 0, sizeof(entity));
    entity.mesh = create_triangle(&app.renderer);
    
    // MainLoop
    app.running = true;
    while (app.running)
    {
        input_reset(&app.input);
        if (!window_handle_event(&app.input))
        {
            app.running = false;
            break;
        }
        input_update(&app.input);
        
        // Camera
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 720.0f, 0.1f, 100.0f);
        int matrix_loc = glGetUniformLocation(shader.id, "projection");
        glUniformMatrix4fv(matrix_loc, 1, GL_FALSE, glm::value_ptr(projection));
        
        local_variable glm::vec3 camera_pos   = glm::vec3(-4.0f, 0.0f, 0.0f);
        local_variable glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, 0.0f);
        local_variable glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
        int view_loc = glGetUniformLocation(shader.id, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        
        // Input Mouse
        local_variable f32 yaw = 0.0f;
        local_variable f32 pitch = 0.0f;
        local_variable f32 xoffset = 0.0f;
        local_variable f32 yoffset = 0.0f;
        
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
        
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front = glm::normalize(direction);
        
        // Input Keyboard
        const f32 camera_speed = 0.05f;
        if (input_is_key_down(&app.input, KeyCode_W))
            camera_pos += camera_speed * camera_front;
        if (input_is_key_down(&app.input, KeyCode_S))
            camera_pos -= camera_speed * camera_front;
        if (input_is_key_down(&app.input, KeyCode_A))
            camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
        if (input_is_key_down(&app.input, KeyCode_D))
            camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
        if (input_is_key_down(&app.input, KeyCode_Q))
            yaw -= 0.5f;
        if (input_is_key_down(&app.input, KeyCode_E))
            yaw += 0.5f;
        
        // Model
        {
            local_variable glm::mat4 transform = glm::mat4(1.0f);
            int model_loc = glGetUniformLocation(shader.id, "model");
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(transform));
        }
        
        renderer_draw(&app.renderer, &shader, &entity);
        window_update(&app.window);
        
        SDL_Delay(1);
    }
    
    return 0;
}