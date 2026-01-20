#pragma once
#include <SDL.h>
#include <InputState.h>
#include <Camera.h>

class Car
{
private:
    // Physics Properties
    float x, z; // position
    float velocity; // velocity
    float acceleration; // acceleration
    float angleInRadians; // Angle
    float angularVelocity; // turn speed
    const float MAXSPEED; // Maximum Speed
    const float ACCELERATIONRATE; // acceleration
    const float DEACCELERATIONRATE; // brake
    const float FRICTIONRATE; // friction
    const float ANGULARVELOCITYRATE; //

    // Car Properties
    int width, height; // car size

public:
    Car(float startX, float startZ, int carWidth, int carHeight, float velocity,
         float startAcceleration, float startAngleInRadians, float startAngularVelocity, float maxSpeed, 
         float accelerationRate, float deAccelerationRate, float frictionRate, float angularVelocityRate);

    void handleInput(const InputState& state);
    void update(float deltaTime, float roadHeading);
    SDL_Rect getRenderRect() const;

    // renderer
    void render(SDL_Renderer* renderer, Camera& camera) const;

    // output methods
    float getVelocityX();
    float getVelocityZ();
    float getX();
    float getZ();
};


