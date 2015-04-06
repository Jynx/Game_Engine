#include "Sprite.h"

Sprite::Sprite() : _vboID(0) {}

Sprite::~Sprite() {
    if(_vboID != 0) {
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

    float vertexData[12];  // x and y, *6
    vertexData[0] = x + width;
    vertexData[1] = y + height;

    vertexData[2] = x;
    vertexData[3] = y + height;

    vertexData[4] = x;
    vertexData[5] = y;

    vertexData[6] = x;
    vertexData[7] = y;

    vertexData[8] = x + width;
    vertexData[9] = y;

    vertexData[10] = x + width;
    vertexData[11] = y + height;

    // telling gl this the active buffer, and type
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    // 1: target, size, pointer to array, usage(draw it x times, once etc.)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the buffer.
}

void Sprite::Draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID); //current active buffer
    
    //use our array of positions. We could send more attribute arrays
    //that have information like lighting, color or intensity.
    glEnableVertexAttribArray(0);
    // pointing gl to start of data, May want to specify starting position
    //position, size of vertex (# of elements, x y), type of var
    // 2 points * float = 8 bytes a time.
    // normalize or not, then stride.
    // pointer for interleaving.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //actually draw. Mode, first element, #of elements(vertices)
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds the buffer.
}
