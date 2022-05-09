#ifndef ALEX_SHADER_H
#define ALEX_SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Shader
{
    u32 id;
};

internal Shader shader_create(const char *vert_path, const char *frag_path);

internal void shader_set_math4(const Shader *shader, const char *name, const glm::mat4 &v);

#endif //ALEX_SHADER_H
