#pragma once
#include <SDL.h>
#include <Constants.h>

class Road
{
private:
    float segmentHeight;
    float segmentWidth;
    float segmentLength;
    float trackLength;
    int horizonY;
public:
    Road(int SegmentHeight, int SegmentWidth, int SegmentLength, int TrackLength, float HorizonY);
    void update(Uint32 deltaTime, float cameraZ);
    void render(SDL_Renderer* renderer);
};