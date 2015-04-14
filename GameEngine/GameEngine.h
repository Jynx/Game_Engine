#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Sengine/Sengine.h>

#include <Sengine/Sprite.h>
#include <Sengine/GLSLProgram.h>
#include <Sengine/OpenGLTexture.h>
#include <Sengine/Window.h>
#include <Sengine/Errors.h>

#include <vector>

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

    Sengine::Window _window;
    SDL_Joystick *joy;

    int _screenWidth;
    int _screenHeight;
    float _time;
    float _fps;
    float _frameTime;
    float _ms;
    float _maxFPS;

	std::vector<Sengine::Sprite*> _sprites;
    
    GameState _gameState;
	Sengine::Sprite _testSprite;

	Sengine::GLSLProgram _colorProg;
};
