#include "alex_sandbox.h"
#include "alex_camera.h"
#include "alex_entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

struct Vertex
{
    glm::vec3 position;
};

struct Renderer_Statistics
{
    u32 quad_count;
};

struct Sandbox
{
    Mesh quad_mesh;
    
    Shader shader;
    Camera3D camera;
};

global_variable Sandbox box;

internal
void sandbox_init()
{
    ZERO_STRUCT(&box);
    
    // Camera
    camera_create(&box.camera);
    
    // Create Shaders
    box.shader = shader_create("./assets/shaders/flat_color.vs", 
                               "./assets/shaders/flat_color.fs");
    
    // Setup QuadMesh
    {
        u32 vbo, vao, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);
        
        local_variable Vertex vertices[] = {
            glm::vec3(0.5f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f,  0.5f, 0.0f),
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        
        local_variable u32 indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0); 
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        box.quad_mesh.id = vao;
    }
}

internal void 
sandbox_on_update()
{
    // Update Camera
    {
        shader_use(box.shader);
        shader_set_math4(box.shader, "u_view_projection", camera_get_matrix(&box.camera));
    }
}

internal void 
sandbox_on_event()
{
    
}

internal void 
sandbox_on_render()
{
    sandbox_draw_quad({ 0.0f, 0.0f, 0.0f });
    sandbox_draw_quad({ 1.0f, 1.0f, 0.0f });
    sandbox_draw_quad({ -1.0f, -1.0f, 0.0f });
}

internal void 
sandbox_draw_quad(const glm::vec3 &position)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
    
    shader_use(box.shader);
    shader_set_math4(box.shader, "u_model", transform);
    renderer_draw(box.shader, box.quad_mesh, 6);
}