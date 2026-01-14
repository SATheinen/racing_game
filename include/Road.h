#pragma once
#include <SDL.h>
#include <Constants.h>
#include <vector>
#include <Camera.h>

struct RoadSegment {
    float worldZ;
    SDL_Color color;
};

class Road
{
private:
    float segmentHeight;
    float segmentWidth;
    float segmentLength;
    float trackLength;
    int horizonY;
    std::vector<RoadSegment> segments;
public:
    Road(float SegmentHeight, float SegmentWidth, float SegmentLength, float TrackLength, float HorizonY);
    void render(SDL_Renderer* renderer, Uint32 deltaTime, Camera& camera);
};