#pragma once
#include <SDL.h>
#include <Car.h>
#include <InputState.h>
#include <HandleInput.h>

class Game
{
private:
    bool gameIsRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Car playerCar;
    InputState inputState;
    HandleInput handleInput;
    float cameraZ;

public:
    Game();
    ~Game();

    bool init();
    void runGame();
    void cleanup();
};