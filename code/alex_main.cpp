#include "alex_input.h"
#include "alex_logger.h"
#include "alex_window.h"
#include "alex_renderer.h"
#include "alex_sandbox.h"

int main(int argc, char *argv[])
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    app.run(); 
    
    return 0;
}