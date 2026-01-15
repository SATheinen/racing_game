#include <Camera.h>
#include <iostream>

Camera::Camera(float startX, float startY, float startZ, float startVelocityZ, float startVelocityX, float fov = FOV)
        : x(startX), y(startY), z(startZ), velocityZ(startVelocityZ), velocityX(startVelocityX), fov(fov) {}

void Camera::update(float deltaTime) {
    z = z + velocityZ * deltaTime;
    x = x + velocityX * deltaTime * fov;
}