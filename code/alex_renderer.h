#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

#include "alex_shader.h"

struct Renderer
{
};

internal void renderer_init(Renderer *renderer);
internal void renderer_draw(Renderer *renderer, const Shader *shader, 
                            const Entity *mesh);

internal Mesh create_triangle(Renderer *renderer);

#endif // ALEX_RENDERER_H