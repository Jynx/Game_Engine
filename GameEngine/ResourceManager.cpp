#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

OpenGLTexture ResourceManager::GetTexture(std::string texturePath) {
	return _textureCache.GetTexture(texturePath);
}