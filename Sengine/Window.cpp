#include "Window.h"

namespace Sengine {
    Window::Window() {}

    Window::~Window() {}

    int Window::Create(std::string win_name, int screen_width, int screen_height,
        unsigned int flags) {

        uint32_t all_flags = SDL_WINDOW_OPENGL;

        if (flags & WIN_HIDDEN) {
            all_flags |= SDL_WINDOW_HIDDEN;
        }

        if (flags & WIN_FULLSCREEN) {
            all_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }

        if (flags & WIN_BORDERLESS) {
            all_flags |= SDL_WINDOW_BORDERLESS;
        }

        //SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        sdl_window_ = SDL_CreateWindow(
            win_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screen_width, screen_height, all_flags);
        if (sdl_window_ == nullptr) {
            FatalError("SDL Window not created");
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(sdl_window_);
        if (glContext == nullptr) {
            FatalError("SDL_GL Context could not be created");
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            FatalError("Glew init error");
        }


        // rbgalpha every time glClear() is called
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        //vsync
        SDL_GL_SetSwapInterval(0);

        printf("   OpenGL Version:  %s\n", glGetString(GL_VERSION));

        return 0;
    }

    void Window::SwapBuffer() {
        SDL_GL_SwapWindow(sdl_window_);
    }

}