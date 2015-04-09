#include "GameEngine.h"
#include <stdio.h>
#include <iostream>
#include <string>

GameEngine::GameEngine()
    : _screenWidth(1024),
      _screenHeight(768),
      _window(nullptr),
      _gameState(GameState::PLAY),
      _time(0) {}

GameEngine::~GameEngine() {}

void GameEngine::Run() {
    InitSystems();
    _testSprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);
    GameLoop();
}

// last arg  in create window is a uint32_t window flag. like fullscreen,
// borderless etc.
void GameEngine::InitSystems() {
    SDL_Init(SDL_INIT_EVERYTHING |
             SDL_INIT_JOYSTICK);  // sets up SDL for running everything.
    _window = SDL_CreateWindow(
        "GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        _screenWidth, _screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (_window == nullptr) {
        FatalError("SDL Window not created");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        FatalError("SDL_GL Context could not be created");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        FatalError("Glew init error");
    }
    // tells SDL we want to double buffer so we can swap too and from.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // rbgalpha every time glClear() is called
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    InitShaders();
}

void GameEngine::InitShaders() {
    _colorProg.CompileShaders("Shaders/colorShader.vert",
                              "Shaders/colorShader.frag");
    _colorProg.AddAttribute("vertexPosition");
    _colorProg.AddAttribute("vertexColor");
    _colorProg.LinkShaders();
}

void GameEngine::GameLoop() {
    while (_gameState != GameState::EXIT) {
        ProcessInput();
        _time += 0.0001;
        DrawGame();
    }
}

void GameEngine::ProcessInput() {
    SDL_Event event;
    if (SDL_NumJoysticks > 0) {
        joy = SDL_JoystickOpen(0);
        // if (joy) {
        //     printf("Opened Joystick 0\n");
        //     printf("Name: %s\n", SDL_JoystickNameForIndex(0));
        //     printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
        //    printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
        //     printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
    } else {
        printf("Couldn't open Joystick 0\n");
    }
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                _gameState = GameState::EXIT;
                break;
            }
            case SDL_JOYAXISMOTION: {
                if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
                    if (event.jaxis.axis == 0) {
                        /* Left-right movement code goes here */
                        std::cout << "left-right movement detected!"
                                  << std::endl;
                    }

                    if (event.jaxis.axis == 1) {
                        printf("Up-Down movement detected");
                        /* Up-Down movement code goes here */
                    }
                }
                break;
            }
            case SDL_JOYBUTTONDOWN: { /* Handle Joystick Button Presses */
                switch (event.jbutton.button) {
                    case (0): {
                        printf("D-Pad Up");
                        break;
                    }
                    case (1): {
                        printf("D-Pad down");
                        break;
                    }
                    case (2): {
                        printf("D-Pad Left");
                        break;
                    }
                    case (3): {
                        printf("D-Pad Right");
                        break;
                    }
                    case (4): {
                        printf("D-Pad Right");
                        break;
                    }
                    case (5): {
                        printf("shoulder");
                        break;
                    }
                    case (6): {
                        printf("shoudler");
                        break;
                    }
                    case (7): {
                        printf("dsfs");
                        break;
                    }
                    case (8): {
                        printf("bbbbt");
                        break;
                    }
                    case (9): {
                        printf("eeee");
                        break;
                    }
                    case (10): {
                        printf("a");
                        break;
                    }
                    case (11): {
                        printf("b");
                        break;
                    }
                    case (12): {
                        printf("x");
                        break;
                    }
                    case (13): {
                        printf("y");
                        break;
                    }

                    default:
                        break;
                }
            } break;
        }
    }
}

void GameEngine::DrawGame() {

    glClearDepth(1.0);  // sets a var to tell opengl what depth to clear to.
    // clears the color/depth buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProg.Bind();
	GLuint timeUniformLoc = _colorProg.GetUniformVarLocation("time");
    glUniform1f(timeUniformLoc, _time);

    _testSprite.Draw();

    _colorProg.UnBind();

    SDL_GL_SwapWindow(_window);
}