#include "alex_application.h"

#include "alex_logger.h"

#include <SDL2/SDL.h>

void Application::init()
{
    running = true;
    
    // Test Log
#if 0
    LOG_INFO("PI: %f", PI);
    LOG_WARN("PI: %f", PI);
    LOG_DEBUG("PI: %f", PI);
    LOG_TRACE("PI: %f", PI);
    LOG_ERROR("PI: %f", PI);
    LOG_FATAL("PI: %f", PI);
#endif
    
    window.init();
}

void Application::run()
{
    while (running)
    {
        if (!window.handle_event())
        {
            running = false;
            break;
        }
        
        window.update();
        
        //LOG_DEBUG("TEST");
        SDL_Delay(1000/144);
    }
}