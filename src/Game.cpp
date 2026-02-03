#include <SDL.h>
#include <SDL_image.h>
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
      playerCar(100.0, 460, 500, 120, 120, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 2.0f, -2.0f, -1.0f, 1.0f),
      road(1000.0f, SAMPLE_SPACING, VISIBLE_DISTANCE, SCREEN_HEIGHT / 2),
      inputState(),
      handleInput(),
      camera(0.0f, static_cast<float>(SCREEN_HEIGHT / 2), 1.0f, 0.0f, 0.0f, FOV) {
}
Game::~Game() {
    if (carTexture) {
        SDL_DestroyTexture(carTexture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

bool Game::init() {
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        cout << "SDL initalising successful" << endl;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
            std::cout << "Error SDL2 Initialization : " << SDL_GetError();
            return 1;
        }

        if (IMG_Init(IMG_INIT_PNG) == 0) {
            std::cout << "Error SDL2_image Initialization";
            return 2;
        }

        window = SDL_CreateWindow("SDL Window",
          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, SDL_WINDOW_SHOWN);

        if(window != 0)
        {
            cout << "Window creation succeeded" << endl;

            renderer = SDL_CreateRenderer(window, -1, 0);

            if (renderer != 0)
            {
                cout << "Renderer creation succeeded" << endl;

                SDL_Surface* carSurface = IMG_Load("sprites/car.png");
                if (!carSurface) {
                    cout << "Failed to load car sprite: " << IMG_GetError() << endl;
                    return false;
                }

                carTexture = SDL_CreateTextureFromSurface(renderer, carSurface);
                SDL_FreeSurface(carSurface);

                if (!carTexture) {
                    cout << "Failed to create car texture: " << SDL_GetError() << endl;
                    return false;
                }

                cout << "Car sprite loaded successfully" << endl;

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

        camera.velocityX = playerCar.getVelocityX();
        camera.velocityZ = playerCar.getVelocityZ();
        camera.update(deltaTime);

        SDL_RenderClear(renderer);
        
        road.render(renderer, deltaTime, camera, playerCar.getDistFromCamera());
        playerCar.render(renderer, camera, carTexture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255); // Screen color
        SDL_RenderPresent(renderer);
    }
}