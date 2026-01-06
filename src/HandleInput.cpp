#include <SDL.h>
#include <HandleInput.h>
#include <InputState.h>

void HandleInput::processEvent(const SDL_Event& event, InputState& state) {
    if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.scancode){
            case SDL_SCANCODE_W:
                state.accelerate = true;
                break;
            case SDL_SCANCODE_S:
                state.brake = true;
                break;
            case SDL_SCANCODE_A:
                state.turnLeft = true;
                break;
            case SDL_SCANCODE_D:
                state.turnRight = true;
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.scancode){
            case SDL_SCANCODE_W:
                state.accelerate = false;
                break;
            case SDL_SCANCODE_S:
                state.brake = false;
                break;
            case SDL_SCANCODE_A:
                state.turnLeft = false;
                break;
            case SDL_SCANCODE_D:
                state.turnRight = false;
                break;
        }
    }
}