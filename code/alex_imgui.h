/* date = May 26th 2022 11:12 am */

#ifndef ALEX_IMGUI_H
#define ALEX_IMGUI_H

#include "alex.h"

internal void imgui_init(App_Context *app);
internal void imgui_release();

internal void imgui_begin();
internal void imgui_end(App_Context *app);

#endif //ALEX_IMGUI_H
