#pragma once
#include "OpenGLTexture.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <string>

class ImageLoader {
public:
    OpenGLTexture LoadImageFromFile(const std::string& filename,
                                    int channelOptions, unsigned int reuseID,
                                    unsigned int flags);
private:
};
