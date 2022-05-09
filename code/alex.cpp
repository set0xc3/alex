#include "alex.h"

#include "alex_input.cpp"
#include "alex_logger.cpp"
#include "alex_window.cpp"
#include "alex_renderer.cpp"
#include "alex_sandbox.cpp"
#include "alex_shader.cpp"
#include "alex_main.cpp"

#include "../third-party/glad/src/glad.c"

internal 
char *get_data_from_file(const char *path)
{
    FILE *file = fopen(path , "r");
    char *str = 0;
    u32 size = 0;
    if (file != 0)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        str = (char*)malloc(size + 1);
        
        fseek(file, 0, SEEK_SET);
        fread(str, 1, (size_t)size, file);
        str[size] = 0;
        
        fclose(file);
        return str;
    }
    return 0;
}