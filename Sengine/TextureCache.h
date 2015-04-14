#pragma once
#include <map>
#include "OpenGLTexture.h"

namespace Sengine {
    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

        OpenGLTexture GetTexture(std::string& texturePath);

    private:
        std::map<std::string, OpenGLTexture> _textureMap;
    };

}