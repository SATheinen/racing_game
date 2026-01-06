#pragma once
#include <SDL.h>

struct InputState {
    bool accelerate = false;
    bool brake = false;
    bool turnLeft = false;
    bool turnRight = false;
};