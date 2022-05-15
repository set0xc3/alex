#include "alex_application.h"

int main(int argc, char *argv[])
{
    Application app;
    memset(&app, 0, sizeof(app));
    
    app.init();
    app.run(); 
    
    return 0;
}