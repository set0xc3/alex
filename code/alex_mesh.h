#ifndef ALEX_MESH_H
#define ALEX_MESH_H

struct Mesh 
{
    u32 id;
    
    u32 vertecs;
    u32 indices;
};

internal void mesh_set_data(const Mesh &mesh, const void* data, const u32 size);

#endif //ALEX_MESH_H
