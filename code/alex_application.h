#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

#include "alex_logger.h"
#include "alex_window.h"

struct Application
{
    b8 running;
    
    Window window;
};
global_variable Application app;

internal void create_application();

#endif //ALEX_APPLICATION_H
