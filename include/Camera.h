#pragma once
#include <SDL.h>
#include <Constants.h>

class Camera
{
public:
    Camera(float x, float y, float z, float velocityZ, float velocityX, float fov);
    float velocityZ, velocityX;
    float x, y, z;
    float fov;
    void update(float deltaTime);
};