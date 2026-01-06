#include <SDL.h>
#include <Car.h>
#include <InputState.h>

Car::Car(float startX, float startY, float startAcceleration, float startAngularVelocity,
    float maxSpeed, float accelerationRate, float deAccelerationRate, 
    float frictionRate, float angularVelocityRate, int carWidth, int carHeight)
    : x(startX), y(startY), velocity(0), angle(0), angularVelocity(startAngularVelocity), 
    MAXSPEED(maxSpeed), acceleration(startAcceleration), ACCELERATIONRATE(accelerationRate), 
    DEACCELERATIONRATE(deAccelerationRate), FRICTIONRATE(frictionRate), 
    ANGULARVELOCITYRATE(angularVelocityRate), width(carWidth), height(carHeight) {
}

void Car::render(SDL_Renderer* renderer) const {
    SDL_Rect carRect;
    carRect.x = static_cast<int>(x);
    carRect.y = static_cast<int>(y);
    carRect.w = width;
    carRect.h = height;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &carRect);
}

void Car::handleInput(const InputState& state) {
    // determine if buttons are pressed
    if (state.accelerate == true) {
        float acceleration = ACCELERATIONRATE;
    }
    else {
        float acceleration = FRICTIONRATE;
    }
    if (state.brake == true) {
        float acceleration = DEACCELERATIONRATE;
    }
    if (state.turnLeft == true) {
        float angularVelocity = ANGULARVELOCITYRATE;
    }
    else if (state.turnLeft == true) {
        float angularVelocity = -ANGULARVELOCITYRATE;
    }
    else {
        float angularVelocity = 0.0f;
    }
}

void Car::update(float deltaTime) {
    // Apply physics
    float velocity = velocity + acceleration * deltaTime;
    float angle = angle + angularVelocity * deltaTime;

    // Respect bounds
    if (velocity < 0.0f) {
        float velocity = 0.0f;
    } else if (velocity > MAXSPEED) {
        float velocity = MAXSPEED;
    }
}