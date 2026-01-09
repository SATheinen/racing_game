#include <SDL.h>
#include "Game.h"
#include "Car.h"
#include <iostream>

using namespace std;

Uint32 lastFrameTime=0.0;

Game::Game()
    : gameIsRunning(true),
      window(nullptr),
      renderer(nullptr),
      playerCar(480, 320, 40, 60, 0.0f, 0.0f, 100.0f, 50.0f, -50.0f, -30.0f, 50.0f),
      inputState(),
      handleInput(),
      cameraZ(0.0f) {
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
        playerCar.update(deltaTime);

        SDL_RenderClear(renderer);

        int horizonY = 320;
        int numSegments = 100;
        float segmentHeight = 80.0f;
        float segmentWidth = 700.0f;
        int trackLength = static_cast<float>(numSegments) * segmentHeight;
        cameraZ += 1.0f * deltaTime;

        if (cameraZ > trackLength / 100.0f) {
            cameraZ -= trackLength / 100.0f;
        }
        cout << cameraZ << "\n";

        for (int i = 0; i < numSegments; i++) {
            float segmentWorldZ = i * 1.0f;
            
            float relativeZ = segmentWorldZ - cameraZ;

            if (relativeZ <= 0.001f) continue;

            float screenY = horizonY + (200.0f / relativeZ);

            float stripHeight = segmentHeight / relativeZ;
            float stripWidth = segmentWidth / relativeZ;

            if (i % 2 == 0){
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            }

            SDL_Rect strip;
            strip.x = static_cast<int>((960 - stripWidth) / 2);
            strip.y = static_cast<int>(screenY);
            strip.w = static_cast<int>(stripWidth);
            strip.h = static_cast<int>(stripHeight);

            SDL_RenderFillRect(renderer, &strip);
        }
        playerCar.render(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255); // Screen color
        SDL_RenderPresent(renderer);
    }
}