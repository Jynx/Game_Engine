#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Sengine.h"

namespace Sengine {
	int Init() {
		SDL_Init(SDL_INIT_EVERYTHING |
			SDL_INIT_JOYSTICK);  // sets up SDL for running everything.

		// tells SDL we want to double buffer so we can swap too and from.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}