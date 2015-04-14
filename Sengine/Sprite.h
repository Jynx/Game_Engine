#pragma once
#include <GL/glew.h>
#include <string>
#include "OpenGLTexture.h"

namespace Sengine {
	class Sprite {
	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height,
			std::string texturePath);
		void Draw();

	private:
		float _x, _y, _width, _height;
		GLuint _vboID;  // guaranteed to be 32 bits.
		OpenGLTexture _texture;
	};
}