
#include "alex.h"
#include "application.h"

int 
main(int arg, char** arv)
{
    Alex::Application app;
    app.run();
    
    return 0;
}

#if 0

// GLM Math
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

// ...

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

// ...

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

// ...


// Draw
transform = glm::translate(transform, glm::vec3(player.x, player.y, player.z));

u32 transformLoc = glGetUniformLocation(shaderProgram, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

#endif // OpenGL