#include <SDL.h>
#include "Game.h"
#include "Car.h"
#include <iostream>
#include "Constants.h"

using namespace std;

Uint32 lastFrameTime=0.0;

Game::Game()
    : gameIsRunning(true),
      window(nullptr),
      renderer(nullptr),
      playerCar(460, 500, 40, 60, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 2.0f, -2.0f, -1.0f, 1.0f),
      road(1000.0f, SAMPLE_SPACING, VISIBLE_DISTANCE, SCREEN_HEIGHT / 2),
      inputState(),
      handleInput(),
      camera(static_cast<float>(SCREEN_WIDTH / 2), static_cast<float>(SCREEN_HEIGHT / 2), 1.0f, 0.0f, 0.0f, FOV) {
}
Game::~Game() {
}

bool Game::init() {
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        cout << "SDL initalising successful" << endl;

        window = SDL_CreateWindow("SDL Window",
          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, SDL_WINDOW_SHOWN);

        if(window != 0)
        {
            cout << "Window creation succeeded" << endl;

            renderer = SDL_CreateRenderer(window, -1, 0);

            if (renderer != 0)
            {
                cout << "Renderer creation succeeded" << endl;

                return true;
            }
            else
            {
                cout << "Renderer creation failed" << endl;
                return false;
            }
        }
        else
        {
            cout << "Window creation failed" << endl;
            return false;
        }
    }
    else
    {
        cout << "SDL initalisation failed" << endl;
        return false;
    }
}

void Game::runGame() {
    SDL_Event event;

    while (gameIsRunning == true)
    {
        // calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f; // convert to seconds
        lastFrameTime = currentTime;

        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                cout << "Quitting application\n";
                gameIsRunning = false;
                break;
            }
            handleInput.processEvent(event, inputState);
        }
        playerCar.handleInput(inputState);
        playerCar.update(deltaTime, road.getRoadAngleAt(playerCar.getZ()));

        camera.z = playerCar.getZ();
        camera.x = playerCar.getX();
        //camera.update(deltaTime);

        SDL_RenderClear(renderer);
        
        road.render(renderer, deltaTime, camera);
        playerCar.render(renderer, camera);
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255); // Screen color
        SDL_RenderPresent(renderer);
    }
}