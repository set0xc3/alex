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

global_variable Vertex quad_vertices[]
{
    glm::vec3(0.5f, 0.5f, 0.0f),
    glm::vec3(0.5f, -0.5f, 0.0f),
    glm::vec3(-0.5f, -0.5f, 0.0f),
    glm::vec3(-0.5f,  0.5f, 0.0f),
};

struct Renderer_Statistics
{
};

struct Sandbox
{
    internal const u32 max_quads         = 1000;
    internal const u32 max_quad_vertices = max_quads * 4;
    internal const u32 max_quad_indices  = max_quads * 6;
    
    u32 quad_index_count = 0;
    
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
    
    // Create Quad
    {
        u32 vbo, vao, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, box.max_quad_vertices, 0, GL_DYNAMIC_DRAW);
        
        u32* indices = (u32*)malloc(box.max_quad_indices * sizeof(u32));
        ZERO_MEMORY(indices);
        
        u32 offset = 0;
		for (u32 i = 0; i < box.max_quad_indices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
            
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
            
			offset += 4;
		}
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, box.max_quad_indices, indices, GL_STATIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0); 
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        box.quad_mesh.id = vao;
        box.quad_mesh.vertecs = 4;
        
        free(indices);
    }
}

internal void 
sandbox_on_update()
{
    // Update Camera
    {
        Camera3D camera;
        camera_create(&camera);
        
        shader_use(box.shader);
        shader_set_math4(box.shader, "u_view_projection", camera_get_matrix(&camera));
    }
}

internal void 
sandbox_on_event()
{
    
}

internal void 
sandbox_on_render()
{
    sandbox_draw_quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    sandbox_draw_quad({ 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
}

internal void 
sandbox_draw_quad(const glm::vec3 &position, const glm::vec3 &size, const glm::vec4 &color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
        * glm::scale(glm::mat4(1.0f), size);
    
    shader_use(box.shader);
    shader_set_math4(box.shader, "u_model", transform);
    mesh_set_data(box.quad_mesh, quad_vertices, sizeof(quad_vertices));
    renderer_draw(box.shader, box.quad_mesh, 6);
}