#ifndef ALEX_SHADER_H
#define ALEX_SHADER_H

struct Shader
{
    u32 id;
};

internal Shader shader_create(const char *vert_path, const char *frag_path);

#endif //ALEX_SHADER_H
