#pragma once
#include <GL/glew.h>

class Sprite {
public:
    Sprite();
    ~Sprite();

    void Init(float x, float y, float width, float height);
    void Draw();
private:
    float _x, _y, _width, _height;
    GLuint _vboID; // guaranteed to be 32 bits.  
};
