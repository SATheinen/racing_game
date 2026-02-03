#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <Car.h>
#include <InputState.h>
#include <Road.h>

Car::Car(float distFromCamera, float startX, float startZ, int carWidth, int carHeight, float startVelocity, 
    float startAcceleration, float startAngleInRadians, float startAngularVelocity, float maxSpeed, 
    float accelerationRate, float deAccelerationRate, float frictionRate, float angularVelocityRate)
    : distFromCamera(distFromCamera), x(startX), z(startZ), width(carWidth), height(carHeight), velocity(0), 
    acceleration(startAcceleration), angularVelocity(startAngularVelocity), angleInRadians(0), 
    MAXSPEED(maxSpeed), ACCELERATIONRATE(accelerationRate), 
    DEACCELERATIONRATE(deAccelerationRate), FRICTIONRATE(frictionRate), 
    ANGULARVELOCITYRATE(angularVelocityRate) {
}

void Car::render(SDL_Renderer* renderer, Camera& camera, SDL_Texture* sprite) const {
    
    SDL_Rect destRect;
    destRect.x = (SCREEN_WIDTH - width) / 2;
    destRect.y = (SCREEN_HEIGHT - height);
    destRect.w = width;
    destRect.h = height;

    double angleDegrees = angleInRadians * 180 / M_PI;
    SDL_RenderCopyEx(renderer, sprite, NULL, &destRect,
                    angleDegrees,
                    NULL,
                    SDL_FLIP_NONE);
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

void Car::update(float deltaTime, float roadHeading) {
    // difference of car and road angle
    float angleDiff = angleInRadians - roadHeading;

    // Apply physics
    angleInRadians = angleInRadians + angularVelocity * deltaTime;
    velocity = velocity + acceleration * deltaTime;

    x = x + velocity * deltaTime * sin(angleDiff);
    z = z + velocity * deltaTime * cos(angleDiff);

    // Respect bounds
    if (velocity < 0.0f) {
        velocity = 0.0f;
    } else if (velocity > MAXSPEED) {
        velocity = MAXSPEED;
    }

    if (angleDiff > 45) {
        angleDiff = 45;
    } else if (angleDiff < -45) {
        angleDiff = -45;
    }

    // decay of turning rate
    angleInRadians = angleInRadians * (1 - deltaTime * 0.8); // Decay of turning angle
}

float Car::getVelocityX() {
    return velocity * sin(angleInRadians);
}

float Car::getVelocityZ() {
    return velocity * cos(angleInRadians);
}

float Car::getX() {
    return x;
}

float Car::getZ() {
    return z;
}

float Car::getDistFromCamera() {
    return distFromCamera;
}