#ifndef ALEX_CAMERA_H
#define ALEX_CAMERA_H

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
    f32 yaw;
    f32 pitch;
    
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    
    glm::mat4 projection;
    glm::mat4 view;
};

struct Camera3D
{
    Transform transform;
    Transform target;
    
    v3 front;
    v3 up;
    
    f32 yaw;
    f32 pitch;
    f32 fov;
    
    m4 view;
    
    u32 projection;
};
//typedef Camera3D Camera;

internal void camera_init(Application *app);
internal void camera_update(Application *app);
internal void camera_on_rescale(Application *app);

internal m4 get_camera_matrix(Camera3D camera);

#endif //ALEX_CAMERA_H
