#pragma once
#include <SOIL/SOIL.h>
#include <GL/Glew.h>
namespace Sengine {
    struct OpenGLTexture {
        GLuint ID;
        int width, height;
    };
}