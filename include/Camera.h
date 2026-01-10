#pragma once
#include <SDL.h>

class Camera
{
private:
    float x, y, z;
public:
    Camera(int x, int y, int z);
    float velocity;
    void update(Uint32 deltaTime);
};