#include "alex_renderer.h"

#include <glad/glad.h>

internal void 
create_renderer(Renderer *renderer)
{
    ZERO_STRUCT(renderer);
    
    renderer->shader = shader_create("./assets/shaders/flat_color.vs", 
                                     "./assets/shaders/flat_color.fs");
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
renderer_draw_line(f32 x, f32 y)
{
    
}

internal void 
renderer_draw_rect(f32 x, f32 y, f32 width, f32 height)
{
    
}

internal void 
renderer_draw_fill_rect(f32 x, f32 y, f32 width, f32 height)
{
    
}