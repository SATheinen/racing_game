#include <Camera.h>

Camera::Camera(int startX, int startY, int startZ)
        : x(startX), y(startY), z(startZ) {}

void Camera::update(Uint32 deltaTime) {
    z += velocity * deltaTime;
}