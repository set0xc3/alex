#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

#include "alex_input.h"
#include "alex_renderer.h"
#include "alex_window.h"

class Application
{
    public:
    
    void run();
    
    public:
    
    b8 running;
    
    Input input;
    Window window;
    Renderer renderer;
};

#endif //ALEX_APPLICATION_H
