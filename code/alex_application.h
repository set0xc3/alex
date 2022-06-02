/* date = June 2nd 2022 1:25 pm */

#ifndef ALEX_APPLICATION_H
#define ALEX_APPLICATION_H

#include "alex_window.h"

struct application_context
{
    b8 quit;
    
    window_context window;
};

internal void init_application();
internal void application_run();

#endif //ALEX_APPLICATION_H
