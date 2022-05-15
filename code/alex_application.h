#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

#include "alex_input.h"
#include "alex_window.h"

class Application
{
    public:
    
    void init();
    void run();
    
    private:
    
    b8 running;
    
    Input input;
    Window window;
};

#endif //ALEX_APPLICATION_H
