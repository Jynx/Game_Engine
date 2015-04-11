#pragma once
#include <GL/glew.h>

// total of 12 bytes.
struct VertexData {
	//vertex positions.
    struct Position {
        float x, y;  // 4 x 2 bytes.
    } position;
    // 1 byte x 4
    struct Color {
        GLubyte r, g, b;
        GLubyte alpha;
    } color;

    //UV texture coordinates
    struct UV {
        float u, v;
    } uv;

    void SetPosition(float x, float y) {
    	position.x = x;
    	position.y = y;
    }

    void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte alpha) {
    	color.r = r;
    	color.g = g;
    	color.b = b;
    	color.alpha = alpha;
    }

    void SetUV(float u, float v) {
    	uv.u = u;
    	uv.v = v;
    }

};
