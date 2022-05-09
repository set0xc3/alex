#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

struct Application
{
    b8 running;
    
    Input input;
    Window window;
    Renderer renderer;
};

#endif //ALEX_APPLICATION_H
