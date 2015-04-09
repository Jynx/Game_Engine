#pragma once
#include <GL/glew.h>

//total of 12 bytes.
struct VertexData {
	struct Position {
		float x, y; // 4 x 2 bytes.
	} position;
	// 1 byte x 4
	struct Color {
		GLubyte r, g, b;
		GLubyte alpha;
	} color;
};