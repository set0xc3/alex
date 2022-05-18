#include "alex_shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

internal Shader 
shader_create(const char *vert_path, const char *frag_path)
{
    Shader shader;
    ZERO_STRUCT(&shader);
    
    char *vertex_shader_source = get_data_from_file(vert_path); 
    if (!vertex_shader_source)
    {
        LOG_ERROR("get_data_from_file failed!");
        return shader;
    }
    char *fragment_shader_source = get_data_from_file(frag_path);
    if (!fragment_shader_source)
    {
        LOG_ERROR("get_data_from_file failed!");
        return shader;
    }
    
    i32 success = false;
    char info_log[256] = "";
    
    // Vertex Shader
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, 0);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, MAX_STR_LEN, 0, info_log);
        LOG_ERROR("Shader vertex compilation failed: %s", info_log);
    }
    
    // Fragment Shader
    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, 0);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, MAX_STR_LEN, 0, info_log);
        LOG_ERROR("Shader fragment compilation failed: %s", info_log);
    }
    
    // Link Shaders
    u32 shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader);
    glAttachShader(shader_program_id, fragment_shader);
    glLinkProgram(shader_program_id);
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shader_program_id, MAX_STR_LEN, 0, info_log);
        LOG_ERROR("Shader program compilation failed: %s", info_log);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    shader.id = shader_program_id;
    
    free(vertex_shader_source);
    free(fragment_shader_source);
    
    LOG_DEBUG("Shader Loaded");
    return shader;
}

internal void 
shader_set_math4(const Shader *shader, const char *name, const glm::mat4 &v)
{
    int loc = glGetUniformLocation(shader->id, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &v[0][0]);
}