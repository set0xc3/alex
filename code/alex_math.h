#ifndef ALEX_MATH_H
#define ALEX_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vector2
{
    f32 x;
    f32 y;
};

struct Vector3
{
    f32 x;
    f32 y;
    f32 z;
};

struct Vector4
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

typedef Vector2 v2;
typedef Vector3 v3;
typedef Vector4 v4;
typedef Vector4 q4;

struct Transform
{
    glm::vec3 position;
    glm::vec4 rotation;
    glm::vec3 scale;
};

struct Matrix
{
    f32 m[16];
};
typedef Matrix m4;

#endif //ALEX_MATH_H
