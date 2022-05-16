#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

#include "alex_mesh.h"
#include "alex_shader.h"

struct Renderer
{
    Shader shader;
};

internal void create_renderer(Renderer *renderer);
internal void renderer_draw(const Shader *shader, const Mesh *mesh);

internal void renderer_set_viewport(i32 x, i32 y, i32 width, i32 height);
internal void renderer_set_color(f32 r, f32 g, f32 b);

// 2D
internal void renderer_draw_line(f32 x, f32 y);
internal void renderer_draw_rect(f32 x, f32 y, f32 width, f32 height);
internal void renderer_draw_fill_rect(f32 x, f32 y, f32 width, f32 height);

#endif //ALEX_RENDERER_H