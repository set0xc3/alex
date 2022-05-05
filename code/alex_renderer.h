#ifndef ALEX_RENDERER_H
#define ALEX_RENDERER_H

struct Shader 
{
    u32 id;
};

struct Texture 
{
    u32 id;
};

typedef Texture Texture2D;

struct Mesh 
{
    u32 vao_id;
    
    f32 *vertices;       // shader location = 0
    u8  *colors;         // shader location = 1
    f32 *texture_coords; // shader location = 2
    u16 *indices;
    
    i32 vertex_count;
    i32 triangle_count;
};

struct Renderer_State
{
    Mesh      mesh;
    Shader    shader;
    Texture2D texture;
};

internal void renderer_init   (Renderer_State *renderer);
internal void renderer_begin  (Renderer_State *renderer);
internal void renderer_submit (Renderer_State *renderer);
internal void renderer_end    (Renderer_State *renderer);

#endif // ALEX_RENDERER_H