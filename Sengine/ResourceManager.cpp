#include "ResourceManager.h"

namespace Sengine {
    TextureCache ResourceManager::_textureCache;

    OpenGLTexture ResourceManager::GetTexture(std::string texturePath) {
        return _textureCache.GetTexture(texturePath);
    }

}