#ifndef ALEX_TEXTURE_H
#define ALEX_TEXTURE_H

struct Texture
{
    u32 id;
    i32 width;
    i32 height;
    i32 format;
};

typedef Texture Texture_2D;

#endif //ALEX_TEXTURE_H
