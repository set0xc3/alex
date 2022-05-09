#ifndef ALEX_ENTITY_H
#define ALEX_ENTITY_H

#include "alex_mesh.h"

struct Entity
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::mat4 transform;
    
    Mesh mesh;
};

#endif //ALEX_ENTITY_H
