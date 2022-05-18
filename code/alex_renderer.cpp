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
    internal const u32 max_quads         = 1000;
    internal const u32 max_quad_vertices = max_quads * 4;
    internal const u32 max_quad_indices  = max_quads * 6;
    
    u32 quad_index_count = 0;
};
global_variable RendererData s_data;

global_variable Vertex vertices[]
{
    { 0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
    { -0.5f,  0.5f, 0.0f },
};

internal void 
create_renderer(Renderer *renderer)
{
    ZERO_STRUCT(renderer);
    
    renderer->shader = shader_create("./assets/shaders/flat_color.vs", 
                                     "./assets/shaders/flat_color.fs");
    // Create Quate
    {
        u32 vbo, vao, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, s_data.max_quad_vertices, 0, GL_DYNAMIC_DRAW);
        
        u32* indices = (u32*)malloc(s_data.max_quad_indices * sizeof(u32));
        ZERO_MEMORY(indices);
        
        u32 offset = 0;
		for (u32 i = 0; i < s_data.max_quad_indices; i += 6)
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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_data.max_quad_indices, indices, GL_STATIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0); 
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        renderer->quad_mesh.id = vao;
        
        free(indices);
    }
    
    // Create Line
    {
        u32 vbo, vao;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, s_data.max_quad_vertices, 0, GL_DYNAMIC_DRAW);
        
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0); 
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        
        renderer->line_mesh.id = vao;
    }
}

internal void 
renderer_draw(const Shader *shader, const Mesh *mesh)
{
    glUseProgram(shader->id);
    glBindVertexArray(mesh->id);
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
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

internal void 
renderer_draw_line(Renderer *renderer, f32 p0[3], f32 p1[3])
{
    Vertex vertices[]
    {
        { p0[0], p0[1], p0[2] },
        { p1[0], p1[1], p1[2] },
    };
    
    glUseProgram(renderer->shader.id);
    
    // Transform
    {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(1.0f));
        transform = glm::translate(transform, glm::vec3(1.0f));
        int model_loc = glGetUniformLocation(renderer->shader.id, "u_model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &transform[0][0]);
    }
    
    // Update data
    {
        glBindBuffer(GL_ARRAY_BUFFER, renderer->line_mesh.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        
        //void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        //memcpy(ptr, vertices, sizeof(vertices));
        //glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    
    glBindVertexArray(renderer->line_mesh.id);
    glDrawArrays(GL_LINES, 0, 2);
    
    // Unbind
    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

internal void 
renderer_draw_rect(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    glUseProgram(renderer->shader.id);
    
    // Transform
    {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(width/100.0f, height/100.0f, 0.0f));
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        int model_loc = glGetUniformLocation(renderer->shader.id, "u_model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &transform[0][0]);
    }
    
    // Update data
    {
        glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_mesh.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        
        //void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        //memcpy(ptr, vertices, sizeof(vertices));
        //glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    
    glBindVertexArray(renderer->quad_mesh.id);
    glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind
    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

internal void 
renderer_draw_fill_rect(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    glUseProgram(renderer->shader.id);
    
    // Transform
    {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(width/100.0f, height/100.0f, 0.0f));
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        int model_loc = glGetUniformLocation(renderer->shader.id, "u_model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &transform[0][0]);
    }
    
    // Update data
    {
        glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_mesh.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        
        //void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        //memcpy(ptr, vertices, sizeof(vertices));
        //glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    
    glBindVertexArray(renderer->quad_mesh.id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind
    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

internal void 
renderer_draw_cube(Renderer *renderer, f32 x, f32 y, f32 width, f32 height)
{
    
}