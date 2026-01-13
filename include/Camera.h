#pragma once
#include <SDL.h>
#include <Constants.h>

class Camera
{
public:
    Camera(float x, float y, float z, float velocity, float fov);
    float velocity;
    float x, y, z;
    float fov;
    void update(float deltaTime);
};