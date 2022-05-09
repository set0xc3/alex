#include "alex_renderer.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

internal 
void renderer_init(Renderer *renderer)
{
    memset(renderer, 0, sizeof(*renderer));
}

internal 
void renderer_draw(Renderer *renderer, const Shader *shader, 
                   const Entity *entity)
{
    glViewport(0, 0, 800, 720);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader->id);
    glBindVertexArray(entity->mesh.vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

internal 
Mesh create_triangle(Renderer *renderer)
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
    
    Mesh mesh = {0};
    
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
    
    mesh.vao_id = VAO;
    return mesh;
}