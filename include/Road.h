#pragma once
#include <SDL.h>
#include <Constants.h>
#include <vector>
#include <Camera.h>

struct RoadSegment {
    float worldZ;
    float curve;
    SDL_Color color;
};

class Road
{
private:
    float segmentWidth;
    float segmentLength;
    float trackLength;
    int horizonY;
    std::vector<RoadSegment> segments;
public:
    Road(float SegmentWidth, float SampleSpacing, float VisibleDistance, float HorizonY);
    void render(SDL_Renderer* renderer, Uint32 deltaTime, Camera& camera);
};