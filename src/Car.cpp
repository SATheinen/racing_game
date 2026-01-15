#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <Car.h>
#include <InputState.h>

Car::Car(float startX, float startY, int carWidth, int carHeight, float startVelocity, 
    float startAcceleration, float startAngle, float startAngularVelocity, float maxSpeed, 
    float accelerationRate, float deAccelerationRate, float frictionRate, float angularVelocityRate)
    : x(startX), y(startY), width(carWidth), height(carHeight), velocity(0), 
    acceleration(startAcceleration), angularVelocity(startAngularVelocity), angle(0), 
    MAXSPEED(maxSpeed), ACCELERATIONRATE(accelerationRate), 
    DEACCELERATIONRATE(deAccelerationRate), FRICTIONRATE(frictionRate), 
    ANGULARVELOCITYRATE(angularVelocityRate) {
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
    angle = angle * (1 - deltaTime * 0.9); // Decay of turning angle
    std::cout << angle << std::endl;
    angle = angle + angularVelocity * deltaTime;
    if (angle > 45) {
        angle = 45;
    } else if (angle < -45) {
        angle = -45;
    }

    float angleInRadians = angle * M_PI / 180;

    velocity = velocity + acceleration * deltaTime;

    // Respect bounds
    if (velocity < 0.0f) {
        velocity = 0.0f;
    } else if (velocity > MAXSPEED) {
        velocity = MAXSPEED;
    }

}

float Car::getVelocityX() {
    float angleInRadians = angle * M_PI / 180;
    return velocity * sin(angleInRadians);
}

float Car::getVelocityZ() {
    float angleInRadians = angle * M_PI / 180;
    return velocity * cos(angleInRadians);
}