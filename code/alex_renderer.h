#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

#include "alex_mesh.h"
#include "alex_shader.h"

struct Renderer
{
    public:
    
    void init();
    void draw(const Shader *shader, const Mesh *mesh);
    
    void set_viewport(i32 x, i32 y, i32 width, i32 height);
    void set_color(f32 r, f32 g, f32 b, f32 a);
    
    private:
};

#endif //ALEX_RENDERER_H