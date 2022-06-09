#include "alex_game.h"
#include "alex_logger.h"

#include <glad/glad.h>

struct vertex_data
{
    f32 pos[3];
    f32 color[4];
};

internal void 
game_startup(game_context *context)
{
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    
    //glEnable(GL_DEPTH_CLAMP);
    //glEnable(GL_CULL_FACE);
    
    context->rendering_program = compile_shaders();
    
    glCreateVertexArrays(1, &context->vertex_array_object);
    glBindVertexArray(context->vertex_array_object);
}

internal void 
game_shutdown(game_context *context)
{
}

internal void 
game_update(game_context *context, f64 dt)
{
    glViewport(0, 0, 1280, 720);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    f32 attrib_offset[] =  
    {
        1.0f,
        0.0f,
        0.0f,
    };
    f32 attrib_color[] =  
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f,
    };
    glVertexAttrib4fv(0, attrib_offset);
    glVertexAttrib4fv(1, attrib_color);
    
    glUseProgram(context->rendering_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

internal void 
game_handle_input(game_context *context)
{
    
}

internal u32 
compile_shaders()
{
    u32 vertex_shader = 0;
    u32 fragment_shader = 0;
    u32 program = 0;
    
    const char *vertex_shader_source = read_from_file("assets/shaders/flat_color.vs.glsl");
    const char *fragment_shader_source = read_from_file("assets/shaders/flat_color.fs.glsl");
    
    // Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, 0);
    glCompileShader(vertex_shader);
    
    // Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, 0);
    glCompileShader(fragment_shader);
    
    // Create program, attach shaders to it, and link it
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    // Clear
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}