#ifndef ALEX_CAMERA_H
#define ALEX_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#endif //ALEX_CAMERA_H
