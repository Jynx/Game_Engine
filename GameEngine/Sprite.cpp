#include "Sprite.h"
#include "VertexData.h"
#include <cstddef>

Sprite::Sprite() : _vboID(0) {}

Sprite::~Sprite() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::Init(float x, float y, float width, float height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // if zero, hasn't been init. Passes in # of buffers, and
    // a reference to the ID, which is switched to a new ID when gl allocates
    // it.

    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);  // create a buffer to pass to gpu
    }

    VertexData vertexData[6];

    vertexData[0].position.x = x + width;
    vertexData[0].position.y = y + height;
    vertexData[0].color.r = 25;
    vertexData[0].color.g = 50;
    vertexData[0].color.b = 255;
    vertexData[0].color.alpha = 255;

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + height;
    vertexData[1].color.r = 255;
    vertexData[1].color.g = 0;
    vertexData[1].color.b = 55;
    vertexData[1].color.alpha = 255;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;
    vertexData[2].color.r = 255;
    vertexData[2].color.g = 100;
    vertexData[2].color.b = 255;
    vertexData[2].color.alpha = 255;
    // triangle deuce
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;
    vertexData[3].color.r = 255;
    vertexData[3].color.g = 100;
    vertexData[3].color.b = 255;
    vertexData[3].color.alpha = 255;

    vertexData[4].position.x = x + width;
    vertexData[4].position.y = y;
    vertexData[4].color.r = 10;
    vertexData[4].color.g = 0;
    vertexData[4].color.b = 255;
    vertexData[4].color.alpha = 255;

    vertexData[5].position.x = x + width;
    vertexData[5].position.y = y + height;
    vertexData[5].color.r = 25;
    vertexData[5].color.g = 50;
    vertexData[5].color.b = 255;
    vertexData[5].color.alpha = 255;
    // telling gl this the active buffer, and type
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    // 1: target, size, pointer to array, usage(draw it x times, once etc.)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbinds the buffer.
}

void Sprite::Draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);  // current active buffer

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

    // actually draw. Mode, first element, #of elements(vertices)
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbinds the buffer.
}
