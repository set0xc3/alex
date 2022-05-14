#include "alex_renderer.h"

#include <glad/glad.h>

internal 
void renderer_init(Renderer *renderer)
{
    memset(renderer, 0, sizeof(*renderer));
}

internal 
void renderer_draw(Renderer *renderer, const Shader *shader, const Mesh *mesh)
{
    glUseProgram(shader->id);
    glBindVertexArray(mesh->vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 6, 0);
}

internal 
void renderer_set_viewport(i32 x, i32 y, i32 width, i32 height)
{
    glViewport(x, y, width, height);
}

internal
void renderer_set_color(f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}