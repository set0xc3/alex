#include "alex_shader.h"

internal 
Shader shader_create(const char *vert_path, const char *frag_path)
{
    Shader shader;
    memset(&shader, 0, sizeof(shader));
    
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
    char info_log[MAX_STR_LEN] = "";
    
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
    
    // Load Texture
    stbi_set_flip_vertically_on_load(true);
    i32 width, height, nr_channels;
    u8 *data = stbi_load("assets/test1.png", &width, &height, &nr_channels, 0); 
    
    // Texture
    u32 texture_id;
    glGenTextures(1, &texture_id);  
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else 
    {
        LOG_ERROR("stbi_load failed");
    }
    stbi_image_free(data);
    
    shader.id = shader_program_id;
    
    free(vertex_shader_source);
    free(fragment_shader_source);
    
    return shader;
}