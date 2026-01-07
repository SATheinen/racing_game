#define _USE_MATH_DEFINES
#include <cmath>

#include <SDL.h>
#include <Car.h>
#include <InputState.h>

Car::Car(float startX, float startY, int carWidth, int carHeight, 
    float startAcceleration, float startAngularVelocity, float maxSpeed, float accelerationRate, 
    float deAccelerationRate, float frictionRate, float angularVelocityRate)
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
        acceleration = ACCELERATIONRATE;
    }
    else {
        acceleration = FRICTIONRATE;
    }
    if (state.brake == true) {
        acceleration = DEACCELERATIONRATE;
    }
    if (state.turnLeft == true) {
        angularVelocity = -ANGULARVELOCITYRATE;
    }
    else if (state.turnRight == true) {
        angularVelocity = ANGULARVELOCITYRATE;
    }
    else {
        angularVelocity = 0.0f;
    }
}

void Car::update(float deltaTime) {
    // Apply physics
    velocity = velocity + acceleration * deltaTime;
    angle = angle + angularVelocity * deltaTime;

    float angleInRadians = angle * M_PI / 180;

    x = x + velocity * deltaTime * sin(angleInRadians);
    y = y - velocity * deltaTime * cos(angleInRadians);

    // Respect bounds
    if (velocity < 0.0f) {
        velocity = 0.0f;
    } else if (velocity > MAXSPEED) {
        velocity = MAXSPEED;
    }
}