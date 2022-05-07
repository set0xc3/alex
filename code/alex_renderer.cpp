#include "alex_renderer.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *vertex_shader_source = 
"    #version 330 core\n"
""
"    layout (location = 0) in vec3 a_position;\n"
"    layout (location = 1) in vec3 a_color;\n"
""
"    out vec3 our_color;\n"
""
"    void main()\n"
"    {\n"
"       gl_Position = vec4(a_position, 1.0);\n"
"       our_color = a_color;\n"
"    }\n\0";

const char *fragment_shader_source = 
"    #version 330 core\n"
""
"    out vec4 FragColor;\n"
""
"    in vec3 our_color;\n"
""
"    void main()\n"
"    {\n"
"       FragColor = vec4(our_color, 1.0f);\n"
"    }\n\0";

internal 
void renderer_init(Renderer_State *renderer)
{
    memset(renderer, 0, sizeof(*renderer));
    
    i32 success = false;
    char info_log[MAX_STR_LEN] = "";
    
    // ----------------------------------------------------------------------------------------------------------
    // Load Shaders
    // ----------------------------------------------------------------------------------------------------------
    
    // Vertex Shader
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
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
        glGetShaderInfoLog(fragment_shader, MAX_STR_LEN, NULL, info_log);
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
        glGetProgramInfoLog(shader_program_id, MAX_STR_LEN, NULL, info_log);
        LOG_ERROR("Shader program compilation failed: %s", info_log);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    // ----------------------------------------------------------------------------------------------------------
    // Load Texture
    // ----------------------------------------------------------------------------------------------------------
    
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
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        LOG_ERROR("stbi_load failed");
    }
    stbi_image_free(data);
    
    renderer->shader.id = shader_program_id;
    
    create_triangle(renderer);
}

internal 
void renderer_draw(Renderer_State *renderer)
{
    glViewport(0, 0, 800, 720);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(renderer->shader.id);
    glBindVertexArray(renderer->mesh.vao_id);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

internal 
void create_triangle(Renderer_State *renderer)
{
    Mesh mesh = {0};
    
    u32 VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    local_variable f32 positions[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
    };
    local_variable u32 indices[] = { 
        0, 1, 2,
    };
    
    // fill buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), 0); 
    glEnableVertexAttribArray(0);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    
    // Texture
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(positions) + sizeof(colors))); 
    //glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    renderer->mesh.vao_id = VAO;
}