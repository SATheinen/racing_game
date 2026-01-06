#include <SDL.h>
#include "Game.h"
#include "Car.h"
#include <iostream>

using namespace std;

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
        SDL_RenderClear(renderer);
        playerCar.render(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255); // Screen color
        SDL_RenderPresent(renderer);
    }
}

Game::Game()
    : gameIsRunning(true),
      window(nullptr),
      renderer(nullptr),
      playerCar(480, 320, 40, 60),
      inputState(),
      handleInput() {
}
Game::~Game() {
}