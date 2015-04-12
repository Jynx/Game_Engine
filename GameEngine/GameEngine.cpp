#include "GameEngine.h"
#include <stdio.h>
#include <iostream>
#include <string>



GameEngine::GameEngine()
    : _screenWidth(1024),
      _screenHeight(768),
      _window(nullptr),
      _gameState(GameState::PLAY),
      _time(0),
      _maxFPS(60.0f) {}

GameEngine::~GameEngine() {}

void GameEngine::Run() {
    InitSystems();
    _sprites.push_back(new Sprite());
    _sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "body_3Dblue.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "body_3Dblue.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->Init(-1.0f, 0.0f, 1.0f, 1.0f, "body_3Dblue.png");
    //_texture = ImageLoader::LoadImageFromFile(
    //  "body_3Dblue.png", 3, 0,
    // SOIL_LOAD_RGBA);
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
    _colorProg.AddAttribute("vertexUV");
    _colorProg.LinkShaders();
}

void GameEngine::GameLoop() {
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks();
        CalculateFPS();
        ProcessInput();
        _time += 0.01;
        DrawGame();

        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 20) {
            printf(" MS: %f , FPS: %f \n", _ms, _fps);
            frameCounter = 0;
        }

        float frameTicks = SDL_GetTicks() - startTicks;
         if (1000.f / _maxFPS > frameTicks) {
             SDL_Delay(1000.f / _maxFPS - frameTicks);
        }
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
    glActiveTexture(GL_TEXTURE0);

    GLint textureLoc = _colorProg.GetUniformVarLocation("tex");
    glUniform1i(textureLoc, 0);

    GLint timeUniformLoc = _colorProg.GetUniformVarLocation("time");
    glUniform1f(timeUniformLoc, _time);
    for (int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->Draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProg.UnBind();

    SDL_GL_SwapWindow(_window);
}

void GameEngine::CalculateFPS() {
    static const int FPS_MAX_SAMPLES = 100;
    static float frameTimes[FPS_MAX_SAMPLES];
    static int frameIndex = 0;
    static float previousTicks = SDL_GetTicks();

    float currentTicks = SDL_GetTicks();
    _frameTime = currentTicks - previousTicks;
    frameTimes[frameIndex % FPS_MAX_SAMPLES] = _frameTime;

    previousTicks = currentTicks;

    //check to see if we've acqrued enough fames
    //to average.
    int frameCount;
    frameIndex++;
    if(frameIndex < FPS_MAX_SAMPLES) {
        frameCount = frameIndex;
    } else {
        frameCount = FPS_MAX_SAMPLES;
    }

    //average all of the samples
    float avgFrameTime = 0;
    for (int i = 0; i < frameCount; i++) {
        avgFrameTime += frameTimes[i];
    }

    avgFrameTime = avgFrameTime / frameCount;

    //calculate ms/fps
    if (avgFrameTime > 0) {
        _fps = 1000.0f / avgFrameTime;
        _ms = avgFrameTime;
    } else {
        _fps = _ms = 60.0f;
    }
    

}
