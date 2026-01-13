#include <Camera.h>
#include <iostream>

Camera::Camera(float startX, float startY, float startZ, float startVelocity, float fov = FOV)
        : x(startX), y(startY), z(startZ), velocity(startVelocity), fov(fov) {}

void Camera::update(float deltaTime) {
    z = z + velocity * deltaTime;
}