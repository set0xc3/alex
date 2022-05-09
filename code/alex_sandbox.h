#ifndef ALEX_SANDBOX_H
#define ALEX_SANDBOX_H

#include "alex_application.h"

internal void sandbox_init(Application *app);

internal void sandbox_on_update(Application *app);
internal void sandbox_on_event(Application *app);
internal void sandbox_on_render(Application *app);

#endif //ALEX_SANDBOX_H
