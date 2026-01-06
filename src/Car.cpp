#include <SDL.h>
#include <Car.h>

Car::Car(float startX, float startY, int carWidth, int carHeight)
    : x(startX), y(startY), velocityX(0.0f), velocityY(0.0f), width(carWidth), height(carHeight) {
}

void Car::render(SDL_Renderer* renderer) const {
    SDL_Rect carRect;
    carRect.x = static_cast<int>(x);
    carRect.y = static_cast<int>(y);
    carRect.w = width;
    carRect.h = height;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &carRect);
}