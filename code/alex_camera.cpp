#include "alex_camera.h"

internal
void camera_init(Camera *camera)
{
    camera->yaw   = 0.0f;
    camera->pitch = 0.0f;
    camera->pos   = glm::vec3(-4.0f, 0.0f, 0.0f);
    camera->front = glm::vec3(0.0f, 0.0f, 0.0f);
    camera->up    = glm::vec3(0.0f, 1.0f, 0.0f);
}

internal
void camera_update(Application *app)
{
    
}

internal
void camera_on_rescale(v2 offset, v2 scale)
{
    
}

internal
m4 get_camera_matrix(Camera3D camera)
{
    return m4();
}