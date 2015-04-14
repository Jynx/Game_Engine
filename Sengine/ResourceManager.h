#pragma once
#include "TextureCache.h"
#include <string>

namespace Sengine {
	class ResourceManager {
	public:
		static OpenGLTexture GetTexture(std::string texturePath);
	private:
		static TextureCache _textureCache;
	};
}