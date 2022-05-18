#include "alex_camera.h"

internal void 
camera_create(Camera *camera)
{
    ZERO_STRUCT(camera);
    
    camera->transform.position = glm::vec3(0.0f, 0.0f, -4.0f);
    camera->transform.scale = glm::vec3(1.0f);
    
    camera->up = { 0.0f, 1.0f, 0.0f };
    
    camera->fov = 45.0f;
    camera->aspect_ratio = 1.778f;
    camera->near_clip = 0.1f;
    camera->far_clip = 1000.0f;
    
    camera->viewport_width = 800.0f;
    camera->viewport_height = 600.0f;
    
    camera->projection_mat = glm::mat4(1.0f);
    camera->view_mat = glm::mat4(1.0f);
    
    camera_update_projection(camera);
    camera_update_view(camera);
}

internal void 
camera_update(Camera* camera)
{
    
}

internal void 
camera_on_rescale(Camera *camera, v2 offset, v2 scale)
{
    camera_update_projection(camera);
}

internal void 
camera_update_projection(Camera* camera)
{
    camera->aspect_ratio = camera->viewport_width / camera->viewport_height;
    camera->projection_mat = glm::perspective(glm::radians(camera->fov), camera->aspect_ratio, camera->near_clip, camera->far_clip);
}

internal void 
camera_update_view(Camera* camera)
{
    camera->view_mat = glm::translate(glm::mat4(1.0f), camera->transform.position); 
}

internal glm::mat4 
camera_get_matrix(Camera* camera)
{
    return camera->projection_mat * camera->view_mat;
}