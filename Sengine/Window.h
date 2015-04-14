#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include "Errors.h"


namespace Sengine {
	enum window_flags {
		WIN_HIDDEN = 0x1,
		WIN_FULLSCREEN = 0x2,
		WIN_BORDERLESS = 0x4
	};

	class Window {
	public:
		Window();
		~Window();

		int Create(std::string win_name, int screen_width, int screen_height,
			unsigned int flags);
		int GetScreenHeight() { return screen_width_; }
		int GetScreenWidth() { return screen_height_; }
		void SwapBuffer();

	private:
		SDL_Window* sdl_window_;
		int screen_width_, screen_height_;

	};
}