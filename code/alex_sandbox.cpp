#include "alex_sandbox.h"
#include "alex_camera.h"
#include "alex_entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Renderer_State
{
};

struct Sandbox
{
    Shader shader;
    Camera camera;
    
    Entity entity;
};

global_variable Sandbox sb;

internal
void sandbox_init(Application *app)
{
    memset(&sb, 0, sizeof(sb));
    
    // Camera
    sb.camera.yaw   = 0.0f;
    sb.camera.pitch = 0.0f;
    sb.camera.pos   = glm::vec3(-4.0f, 0.0f, 0.0f);
    sb.camera.front = glm::vec3(0.0f, 0.0f, 0.0f);
    sb.camera.up    = glm::vec3(0.0f, 1.0f, 0.0f);
    
    
    // Create Shaders
    sb.shader = shader_create("assets/shaders/flat_color.vs", 
                              "assets/shaders/flat_color.fs");
    // Create Triangle
    {
        local_variable Vertex vertecs[]
        {
            { 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
            { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f },
        };
        
        local_variable u32 indices[] = 
        { 
            0, 1, 3,
            1, 2, 3,
        };
        
        u32 VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        // fill buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertecs), vertecs, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), 0); 
        glEnableVertexAttribArray(0);
        
        // Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);
        
        // Texture
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(positions) + sizeof(colors))); 
        //glEnableVertexAttribArray(2);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        sb.entity.mesh.vao_id = VAO;
    }
    
    
}

internal
void sandbox_on_update(Application *app)
{
}

internal
void sandbox_on_event(Application *app)
{
    if(sb.camera.pitch > 89.0f)
        sb.camera.pitch = 89.0f;
    if(sb.camera.pitch < -89.0f)
        sb.camera.pitch = -89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(sb.camera.yaw)) * cos(glm::radians(sb.camera.pitch));
    direction.y = sin(glm::radians(sb.camera.pitch));
    direction.z = sin(glm::radians(sb.camera.yaw)) * cos(glm::radians(sb.camera.pitch));
    sb.camera.front = glm::normalize(direction);
    
    // Input Camera
    {
#if 0
        f32 speed = 0.05f;
        if (input_is_key_down(&app->input, KeyCode_W))
            sb.camera.pos += speed * sb.camera.front;
        if (input_is_key_down(&app->input, KeyCode_S))
            sb.camera.pos -= speed * sb.camera.front;
        if (input_is_key_down(&app->input, KeyCode_A))
            sb.camera.pos -= glm::normalize(glm::cross(sb.camera.front, sb.camera.up)) * speed;
        if (input_is_key_down(&app->input, KeyCode_D))
            sb.camera.pos += glm::normalize(glm::cross(sb.camera.front, sb.camera.up)) * speed;
        if (input_is_key_down(&app->input, KeyCode_Q))
            sb.camera.yaw -= 0.5f;
        if (input_is_key_down(&app->input, KeyCode_E))
            sb.camera.yaw += 0.5f;
#endif
    }
    
    // Input Entity
    {
        f32 speed = 0.05f;
        if (input_is_key_down(&app->input, KeyCode_W))
            sb.entity.position.x += speed;
        if (input_is_key_down(&app->input, KeyCode_S))
            sb.entity.position.x -= speed;
        if (input_is_key_down(&app->input, KeyCode_A))
            sb.entity.position.z -= speed;
        if (input_is_key_down(&app->input, KeyCode_D))
            sb.entity.position.z += speed;
    }
}

internal
void sandbox_on_render(Application *app)
{
    renderer_set_viewport(0, 0, 800, 600);
    renderer_set_color(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Camera
    {
        sb.camera.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shader_set_math4(&sb.shader, "projection", sb.camera.projection);
        
        sb.camera.view = glm::lookAt(sb.camera.pos, sb.camera.pos + sb.camera.front, sb.camera.up);
        shader_set_math4(&sb.shader, "view", sb.camera.view);
    }
    
    // Model
    {
        sb.entity.transform = glm::mat4(1.0f);
        sb.entity.transform = glm::translate(sb.entity.transform, sb.entity.position); 
        shader_set_math4(&sb.shader, "model", sb.entity.transform);
    }
    
    renderer_draw(&app->renderer, &sb.shader, &sb.entity.mesh);
}