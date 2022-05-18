#include "alex_mesh.h"

#include <glad/glad.h>

internal void 
mesh_set_data(const Mesh &mesh, const void* data, const u32 size)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh.id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}