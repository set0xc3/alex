#ifndef ALEX_MESH_H
#define ALEX_MESH_H

struct Vertex
{
    f32 position[3];
};

struct Mesh 
{
    u32 vao_id;
    u32 indices;
};

#endif //ALEX_MESH_H
