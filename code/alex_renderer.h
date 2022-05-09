#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

#include "alex_mesh.h"
#include "alex_shader.h"

struct Renderer
{
};

internal void renderer_init(Renderer *renderer);
internal void renderer_draw(Renderer *renderer, const Shader *shader, const Mesh *mesh);

internal void renderer_set_viewport(i32 x, i32 y, i32 width, i32 height);
internal void renderer_set_color(f32 r, f32 g, f32 b, f32 a);

#endif //ALEX_RENDERER_H