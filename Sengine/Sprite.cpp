#include "Sprite.h"
#include "VertexData.h"
#include "ResourceManager.h"
#include <cstddef>

namespace Sengine {
	Sprite::Sprite() : _vboID(0) {}

	Sprite::~Sprite() {
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::Init(float x, float y, float width, float height,
		std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_texture = ResourceManager::GetTexture(texturePath);

		// if zero, hasn't been init. Passes in # of buffers, and
		// a reference to the ID, which is switched to a new ID when gl allocates
		// it.

		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);  // create a buffer to pass to gpu
		}

		VertexData vertexData[6];

		vertexData[0].SetPosition(x + width, y + height);
		vertexData[0].SetColor(25, 50, 255, 255);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(x, y + height);
		vertexData[1].SetColor(255, 0, 55, 255);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetColor(255, 100, 255, 255);
		vertexData[2].SetUV(0.0f, 0.0f);
		// triangle deuce
		vertexData[3].SetPosition(x, y);
		vertexData[3].SetColor(255, 100, 255, 255);
		vertexData[3].SetUV(0.0f, 0.0f);

		vertexData[4].SetPosition(x + width, y);
		vertexData[4].SetColor(10, 0, 255, 255);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5].SetPosition(x + width, y + height);
		vertexData[5].SetColor(25, 50, 255, 255);
		vertexData[5].SetUV(1.0f, 1.0f);
		// telling gl this the active buffer, and type
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		// 1: target, size, pointer to array, usage(draw it x times, once etc.)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
			GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbinds the buffer.
	}

	void Sprite::Draw() {
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);  // current active buffer

		glBindTexture(GL_TEXTURE_2D, _texture.ID);

		// use our array of positions. We could send more attribute arrays
		// that have information like lighting, color or intensity.
		glEnableVertexAttribArray(0);
		// pointing gl to start of data, May want to specify starting position
		// position, size of vertex (# of elements, x y), type of var
		// 2 points * float = 8 bytes a time.
		// normalize or not, then stride (size of vertex data)
		// pointer for interleaving (offset in struct for position. **position
		// attrib pointer**
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
			(void*)offsetof(VertexData, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData),
			(void*)offsetof(VertexData, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
			(void*)offsetof(VertexData, uv));

		// actually draw. Mode, first element, #of elements(vertices)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbinds the buffer.
	}
}