#pragma once
#include <SDL.h>
#include <InputState.h>

class HandleInput
{
public:
    void processEvent(const SDL_Event& event, InputState& state);
};