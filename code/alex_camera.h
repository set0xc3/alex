#ifndef ALEX_CAMERA_H
#define ALEX_CAMERA_H

#include "alex_math.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Mode
{
    Camera_Custom = 0,
    Camera_Free,
    Camera_Orbital,
    Camera_First_Person,
    Camera_Third_Person
};

enum Camera_Projection
{
    Camera_Perspective = 0,
    Camera_Orthographic,
};

struct Camera
{
    Transform transform;
    Transform target;
    
    v3 front;
    v3 up;
    
    f32 yaw;
    f32 pitch;
    f32 distance;
    
    f32 fov;
    f32 aspect_ratio;
    f32 near_clip;
    f32 far_clip;
    
    f32 viewport_width;
    f32 viewport_height;
    
    glm::mat4 projection_mat;
    glm::mat4 view_mat;
    glm::mat4 view_projection_mat;
};
typedef Camera Camera3D;

internal void camera_create(Camera *camera);
internal void camera_update(Camera *camera);
internal void camera_on_rescale(Camera *camera, v2 offset, v2 scale);

internal void camera_update_projection(Camera* camera);
internal void camera_update_view(Camera* camera);

internal glm::mat4 camera_get_matrix(Camera* camera);

#endif //ALEX_CAMERA_H
