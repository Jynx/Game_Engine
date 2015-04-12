#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "Errors.h"
#include "OpenGLTexture.h"

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
    void CalculateFPS();

    SDL_Window *_window;
    SDL_Joystick *joy;

    int _screenWidth;
    int _screenHeight;
    float _time;
    float _fps;
    float _frameTime;
    float _ms;
    float _maxFPS;
    float _numFrames;
    float _lastTime;

    std::vector<Sprite*> _sprites;
    
    GameState _gameState;
    Sprite _testSprite;

    GLSLProgram _colorProg;
};
