#pragma once
#include <SDL.h>
#include <InputState.h>

class Car
{
private:
    // Physics Properties
    float x, y; // position
    float velocity; // velocity
    float acceleration; // acceleration
    float angle; // Angle
    float angularVelocity; // turn speed
    const float MAXSPEED; // Maximum Speed
    const float ACCELERATIONRATE; // acceleration
    const float DEACCELERATIONRATE; // brake
    const float FRICTIONRATE; // friction
    const float ANGULARVELOCITYRATE; //

    // Car Properties
    int width, height; // car size

public:
    Car(float startX, float startY, float startAcceleration, float startAngularVelocity,
    float maxSpeed, float accelerationRate, float deAccelerationRate, 
    float frictionRate, float angularVelocityRate, int carWidth, int carHeight);

    void handleInput(const InputState& state);
    void update(float deltaTime);
    SDL_Rect getRenderRect() const;

    // input methods
    void accelerate();
    void brake();
    void turnLeft();
    void turnRight();

    // renderer
    void render(SDL_Renderer* renderer) const;
};


