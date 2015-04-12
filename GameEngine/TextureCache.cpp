#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache() {}

TextureCache::~TextureCache() {}

//check for texture in map
OpenGLTexture TextureCache::GetTexture(std::string& texturePath) {
    
    auto itr = _textureMap.find(texturePath);
    //not found
    if (itr == _textureMap.end()) {
    	OpenGLTexture newTexture = ImageLoader::LoadImageFromFile(texturePath, 3, 0, SOIL_LOAD_AUTO);
    	_textureMap.insert(make_pair(texturePath, newTexture));
    	return newTexture;
    }
    //found
    return itr->second;
}