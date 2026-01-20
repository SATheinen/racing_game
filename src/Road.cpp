#include <Road.h>
#include <iostream>
#include <cmath>

Road::Road(float SegmentWidth, float SampleSpacing, float VisibleDistance, float HorizonY)
    : segmentWidth(SegmentWidth), segmentLength(SampleSpacing),
    trackLength(VisibleDistance), horizonY(HorizonY) {

    segments.reserve(NUM_ROAD_SAMPLES);

    float currentX = 0.0f;
    float currentHeading = 0.0f;

    for (int i = 0; i < NUM_ROAD_SAMPLES; i++) {
        RoadSegment seg;
        seg.worldZ = static_cast<float>(i) * segmentLength;
        seg.worldX = currentX;
        seg.heading = currentHeading;

        // define curve
        seg.curve = 10.0f * sin(i * 0.01f);

        segments.push_back(seg);

        // update heading and x for next element
        currentX += seg.curve * segmentLength;
        currentHeading += sin(currentHeading) * segmentLength;
    }
}

void Road::render(SDL_Renderer* renderer, Uint32 deltaTime, Camera& camera) {

    if (camera.z > trackLength / 1.0f) {
        camera.z -= trackLength / 1.0f;
    }

    for (int i = 0; i < segments.size() -1; i++) {
        const RoadSegment& seg = segments[i];
        const RoadSegment& nextSeg = segments[i + 1];

        // Calculate seg center
        float roadCenterX = SCREEN_WIDTH / 2;
        float curveOffset = seg.curve * (camera.z - seg.worldZ);

        // Calculate realtive position
        float relativeZ = seg.worldZ - camera.z;
        float nextRelativeZ = nextSeg.worldZ - camera.z;

        // Skip if behind camera
        if (relativeZ < 0.1f) continue;

        // Calculate screen positions
        float screenY = horizonY + (camera.y / relativeZ) * camera.fov;
        float nextScreenY = horizonY + (camera.y / nextRelativeZ) * camera.fov;

        // Calculate strip dimensions
        float stripHeight = nextScreenY - screenY;
        float stripWidth = (segmentWidth / relativeZ) * camera.fov;

        if (i % 2 == 0) {
            SDL_SetRenderDrawColor(renderer, 100, static_cast<int>(i) * 255 / NUM_ROAD_SAMPLES, 100, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, static_cast<int>(i) * 255 / NUM_ROAD_SAMPLES, 100, 100, 255);
        }

        SDL_Rect strip;
        strip.x = static_cast<int>((SCREEN_WIDTH - static_cast<int>(stripWidth) / 2 - camera.x + curveOffset));
        strip.y = static_cast<int>(screenY);
        strip.w = static_cast<int>(stripWidth);
        strip.h = static_cast<int>(stripHeight);

        SDL_RenderFillRect(renderer, &strip);
    }
}

float Road::getRoadAngleAt(float z) {
    return segments[static_cast<int>(z / SAMPLE_SPACING)].heading;
}