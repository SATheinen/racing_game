#pragma once
#include <SDL.h>
#include <Car.h>
#include <InputState.h>
#include <HandleInput.h>
#include <Road.h>
#include <Camera.h>

class Game
{
private:
    bool gameIsRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Car playerCar;
    Road road;
    Camera camera;
    InputState inputState;
    HandleInput handleInput;

public:
    Game();
    ~Game();

    bool init();
    void runGame();
    void cleanup();
};