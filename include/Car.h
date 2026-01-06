#pragma once
#include <SDL.h>

class Car
{
private:
    float x, y; // position
    float velocityX, velocityY; // velocity
    int width, height; // car size

public:
    Car(float startX, float startY, int carWidth, int carHeight);
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


