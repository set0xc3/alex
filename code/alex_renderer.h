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
    
    u32 indices;
    
    i32 vertex_count;
    i32 triangle_count;
};

struct Renderer_State
{
    Mesh      mesh;
    Shader    shader;
    Texture2D texture;
};

internal void renderer_init (Renderer_State *renderer);
internal void renderer_draw (Renderer_State *renderer);

internal void create_triangle (Renderer_State *renderer);

#endif // ALEX_RENDERER_H