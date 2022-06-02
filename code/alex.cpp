#if 0
// IMGUI
#include "imgui.cpp"
#include "imgui_widgets.cpp"
#include "imgui_tables.cpp"
#include "imgui_draw.cpp"
#include "imgui_demo.cpp"
#include "imgui_impl_opengl3.cpp"
#include "imgui_impl_glfw.cpp"
#endif

// Engine
#include "alex_base_def.h"
#include "alex.h"

#include "alex_application.cpp"
#include "alex_game.cpp"
#include "alex_renderer.cpp"
#include "alex_logger.cpp"
#include "alex_main.cpp"
#include "alex_window.cpp"

internal 
char *read_from_file(const char *path)
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