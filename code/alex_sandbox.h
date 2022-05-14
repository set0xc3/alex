#ifndef ALEX_SANDBOX_H
#define ALEX_SANDBOX_H

#include "alex_application.h"

internal void sandbox_init(Application *app);

// Callbacks
internal void sandbox_on_update(Application *app);
internal void sandbox_on_event(Application *app);
internal void sandbox_on_render(Application *app);

internal void sandbox_begin_camera(Camera camera);
internal void sandbox_create_shaders();

// Draw
internal void sandbox_draw_line(Application *app);
internal void sandbox_draw_square(Application *app);
internal void sandbox_draw_cube(Application *app);
internal void sandbox_draw_plane(Application *app);
internal void sandbox_draw_sphere(Application *app);

// Mesh
internal Mesh sandbox_create_square_mesh();
internal Mesh sandbox_create_cube_mesh();
internal Mesh sandbox_create_sphere_mesh();


#endif //ALEX_SANDBOX_H
