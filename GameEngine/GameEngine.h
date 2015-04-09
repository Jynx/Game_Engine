#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "Errors.h"

class GameEngine {
public:

    enum class GameState {PLAY, EXIT};

    GameEngine();
    ~GameEngine();

    void Run();
    

private:
    void InitSystems();
    void InitShaders();
    void GameLoop();
    void ProcessInput();
    void DrawGame();

    SDL_Window *_window;
    SDL_Joystick *joy;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _time;

    Sprite _testSprite;

    GLSLProgram _colorProg;
};
