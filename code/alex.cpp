#include "alex.h"

#include <stdio.h>

#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

global_variable bool applicaton_quit = false;
global_variable i32 screen_width = 1280;
global_variable i32 screen_height = 720;
global_variable SDL_Window* window = 0;

// OpenGL
global_variable SDL_GLContext context = 0;
global_variable GLuint program_id = 0;
global_variable GLint vertex_pos_2d_location = -1;
global_variable GLuint vbo = 0;
global_variable GLuint ibo = 0;

f32 vertices[] =
{
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

u32 indices[] =
{  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\n"
"uniform mat4 transform;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0f);\n"
"}\0";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int 
main(int arg, char** arv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_GL_LoadLibrary(0); // Default OpenGL is fine.
    
    // Create Window
    u32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, flags);
    if(!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    //Create context
    context = SDL_GL_CreateContext(window);
    if(!context)
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    
    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    
    // Initialize GLAD 
    if (!gladLoadGL())
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    
    // Use Vsync
    if(SDL_GL_SetSwapInterval(true) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }
    
    // OpengGL
    u32 VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);
    
    u32 VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    u32 EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    
    i32 success;
    char infoLog[512];
    
    // Create VertexShader
    u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);
    }
    
    // Create FragmentShader
    u32 fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }
    
    // Create ShaderProgram
    u32 shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
    }
    
    glUseProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);  
    
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
    
    // NOTE(alex): remove this.
    SDL_Delay(50);
    
    while (!applicaton_quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                {
                    applicaton_quit = true;
                    break;
                }
            }
        }
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw
        transform = glm::rotate(transform, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
        
        u32 transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        SDL_GL_SwapWindow(window);
        
        SDL_Delay(1);
    }
    return 0;
}
