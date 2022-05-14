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
    
    Entity entities[256];
    i32 entity_count;
    
    Mesh square;
    Mesh cube;
    Mesh sphere;
};

global_variable Sandbox box;

internal
void sandbox_init(Application *app)
{
    memset(&box, 0, sizeof(box));
    
    // Camera
    box.camera.yaw   = 0.0f;
    box.camera.pitch = 0.0f;
    box.camera.pos   = glm::vec3(-4.0f, 0.0f, 0.0f);
    box.camera.front = glm::vec3(0.0f, 0.0f, 0.0f);
    box.camera.up    = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Create Shaders
    sandbox_create_shaders();
    
    // Create Triangle
    box.square = sandbox_create_square_mesh();
    box.cube   = sandbox_create_cube_mesh();
    box.sphere = sandbox_create_sphere_mesh();
}

internal
void sandbox_on_update(Application *app)
{
}

internal
void sandbox_on_event(Application *app)
{
    if (input_is_mouse_down(&app->input, MouseButton_Right))
    {
        v2 delta = input_get_mouse_delta(&app->input);
        f32 sen = 0.4f;
        box.camera.yaw   += delta.x * sen;
        box.camera.pitch += delta.y * sen;
        
        //LOG_DEBUG("mouse:delta2(%f,%f)", delta.x, delta.y);
    }
    
    if(box.camera.pitch > 89.0f)
        box.camera.pitch = 89.0f;
    if(box.camera.pitch < -89.0f)
        box.camera.pitch = -89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(box.camera.yaw)) * cos(glm::radians(box.camera.pitch));
    direction.y = sin(glm::radians(-box.camera.pitch));
    direction.z = sin(glm::radians(box.camera.yaw)) * cos(glm::radians(box.camera.pitch));
    box.camera.front = glm::normalize(direction);
    
    // Input Camera
    {
#if 1
        f32 speed = 0.05f;
        if (input_is_key_down(&app->input, KeyCode_W))
            box.camera.pos += speed * box.camera.front;
        if (input_is_key_down(&app->input, KeyCode_S))
            box.camera.pos -= speed * box.camera.front;
        if (input_is_key_down(&app->input, KeyCode_A))
            box.camera.pos -= glm::normalize(glm::cross(box.camera.front, box.camera.up)) * speed;
        if (input_is_key_down(&app->input, KeyCode_D))
            box.camera.pos += glm::normalize(glm::cross(box.camera.front, box.camera.up)) * speed;
        if (input_is_key_down(&app->input, KeyCode_Q))
            box.camera.yaw -= 0.5f;
        if (input_is_key_down(&app->input, KeyCode_E))
            box.camera.yaw += 0.5f;
#endif
    }
    
    // Input Entity
    {
#if 0
        f32 speed = 0.05f;
        if (input_is_key_down(&app->input, KeyCode_W))
            box.entity.position.x += speed;
        if (input_is_key_down(&app->input, KeyCode_S))
            box.entity.position.x -= speed;
        if (input_is_key_down(&app->input, KeyCode_A))
            box.entity.position.z -= speed;
        if (input_is_key_down(&app->input, KeyCode_D))
            box.entity.position.z += speed;
#endif
    }
}

internal
void sandbox_on_render(Application *app)
{
    renderer_set_viewport(0, 0, 800, 600);
    renderer_set_color(0.08f, 0.08f, 0.08f, 1.0f);
    
    sandbox_begin_camera(box.camera);
    
    // Camera
    {
        box.camera.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shader_set_math4(&box.shader, "projection", box.camera.projection);
        
        box.camera.view = glm::lookAt(box.camera.pos, box.camera.pos + box.camera.front, box.camera.up);
        shader_set_math4(&box.shader, "view", box.camera.view);
    }
    
    sandbox_draw_square(app);
}

internal 
void sandbox_begin_camera(Camera camera)
{
    box.camera = camera;
}

internal
void sandbox_create_shaders()
{
    
    box.shader = shader_create("./assets/shaders/flat_color.vs", 
                               "./assets/shaders/flat_color.fs");
}

// Draw

internal
void sandbox_draw_line(Application *app)
{
}

internal
void sandbox_draw_square(Application *app)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.0f)); 
    shader_set_math4(&box.shader, "model", transform);
    
    renderer_draw(&app->renderer, &box.shader, &box.square);
}

internal void sandbox_draw_cube(Application *app)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.0f)); 
    shader_set_math4(&box.shader, "model", transform);
    
    renderer_draw(&app->renderer, &box.shader, &box.cube);
}

internal void sandbox_draw_plane(Application *app)
{
}

internal
void sandbox_draw_sphere(Application *app)
{
}

// Mesh

internal
Mesh sandbox_create_square_mesh()
{
    Mesh out_mesh = {0};
    
    local_variable Vertex vertecs[]
    {
        { 0.5f, 0.5f, 0.0f },
        { 0.5f, -0.5f, 0.0f },
        { -0.5f, -0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f },
    };
    local_variable i32 indices[] = 
    {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    u32 vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecs), vertecs, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0); 
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    out_mesh.vao_id = vao;
    return out_mesh;
}

internal 
Mesh sandbox_create_cube_mesh()
{
    Mesh out_mesh = {0};
    
    local_variable Vertex vertecs[]
    {
        { -0.5f, -0.5f, -0.5f }, 
        { 0.5f, -0.5f, -0.5f },  
        { 0.5f,  0.5f, -0.5f },  
        { 0.5f,  0.5f, -0.5f },  
        { -0.5f,  0.5f, -0.5f }, 
        { -0.5f, -0.5f, -0.5f }, 
        
        { -0.5f, -0.5f,  0.5f }, 
        { 0.5f, -0.5f,  0.5f },  
        { 0.5f,  0.5f,  0.5f },  
        { 0.5f,  0.5f,  0.5f },  
        { -0.5f,  0.5f,  0.5f }, 
        { -0.5f, -0.5f,  0.5f }, 
        
        { -0.5f,  0.5f,  0.5f }, 
        { -0.5f,  0.5f, -0.5f }, 
        { -0.5f, -0.5f, -0.5f }, 
        { -0.5f, -0.5f, -0.5f }, 
        { -0.5f, -0.5f,  0.5f }, 
        { -0.5f,  0.5f,  0.5f }, 
        
        { 0.5f,  0.5f,  0.5f },  
        { 0.5f,  0.5f, -0.5f },  
        { 0.5f, -0.5f, -0.5f },  
        { 0.5f, -0.5f, -0.5f },  
        { 0.5f, -0.5f,  0.5f },  
        { 0.5f,  0.5f,  0.5f },  
        
        { -0.5f, -0.5f, -0.5f }, 
        { 0.5f, -0.5f, -0.5f },  
        { 0.5f, -0.5f,  0.5f },  
        { 0.5f, -0.5f,  0.5f },  
        { -0.5f, -0.5f,  0.5f }, 
        { -0.5f, -0.5f, -0.5f }, 
        
        { -0.5f,  0.5f, -0.5f }, 
        { 0.5f,  0.5f, -0.5f },  
        { 0.5f,  0.5f,  0.5f },  
        { 0.5f,  0.5f,  0.5f },  
        { -0.5f,  0.5f,  0.5f }, 
        { -0.5f,  0.5f, -0.5f }, 
    };
    
    u32 vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecs), vertecs, GL_STATIC_DRAW);
    
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0); 
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    out_mesh.vao_id = vao;
    return out_mesh;
}

internal
Mesh sandbox_create_sphere_mesh()
{
    return Mesh();
}