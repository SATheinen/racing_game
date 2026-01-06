#include <SDL.h>
#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    if (game.init())
    {
        cout << "Ready to game!" << endl;
        game.runGame();
    }
    else
    {
        cout << "Initialization failed" << endl;
    }
    return 0;
}