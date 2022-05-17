#include "alex_renderer.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    f32 position[3];
};

struct RendererData
{
    internal const u32 max_quads    = 20000;
    internal const u32 max_vertices = max_quads * 4;
    internal const u32 max_indices  = max_quads * 6;
    
    u32 quad_index_count = 0;
};
global_variable RendererData g_data;

internal void 
create_renderer(Renderer *renderer)
{
    ZERO_STRUCT(renderer);
    
    renderer->shader = shader_create("./assets/shaders/flat_color.vs", 
                                     "./assets/shaders/flat_color.fs");
    // Create Quate
    {
        local_variable Vertex vertices[]
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0); 
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        renderer->mesh.vao_id = vao;
        renderer->mesh.indices = ARRAY_SIZE(indices);
        
        LOG_DEBUG("Mesh_id: %u", vao);
        LOG_DEBUG("Mesh_size: %u", 1024 * sizeof(Vertex));
        LOG_DEBUG("Mesh_vertices: %u", ARRAY_SIZE(vertices));
        LOG_DEBUG("Mesh_indices: %u", ARRAY_SIZE(indices));
    }
}

internal void 
renderer_draw(const Shader *shader, const Mesh *mesh)
{
    glUseProgram(shader->id);
    glBindVertexArray(mesh->vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 6, 0);
}

internal void 
renderer_set_viewport(i32 x, i32 y, i32 width, i32 height)
{
    glViewport(x, y, width, height);
}

internal void 
renderer_set_color(f32 r, f32 g, f32 b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

internal void 
renderer_draw_line(Renderer *renderer, f32 x, f32 y)
{
    
}

internal void 
renderer_draw_rect(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    glUseProgram(renderer->shader.id);
    glBindVertexArray(renderer->mesh.vao_id);
    
    glDrawElements(GL_TRIANGLES, renderer->mesh.indices, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}

internal void 
renderer_draw_fill_rect(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    
}

internal void 
renderer_draw_cube(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    
}