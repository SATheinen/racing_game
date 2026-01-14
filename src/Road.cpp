#include <Road.h>
#include <iostream>

Road::Road(float SegmentHeight, float SegmentWidth, float SegmentLength, float TrackLength, float HorizonY)
    : segmentHeight(SegmentHeight), segmentWidth(SegmentWidth), segmentLength(SegmentLength),
    trackLength(TrackLength), horizonY(HorizonY) {

    segments.reserve(NUM_SEGMENTS);
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        RoadSegment seg;
        seg.worldZ = static_cast<float>(i) * segmentLength + 0.1f;
        segments.push_back(seg);
    }
}

void Road::render(SDL_Renderer* renderer, Uint32 deltaTime, Camera& camera) {

    if (camera.z > trackLength / 1.0f) {
        camera.z -= trackLength / 1.0f;
    }

    for (int i = 0; i < segments.size() -1; i++) {
        const RoadSegment& seg = segments[i];
        const RoadSegment& nextSeg = segments[i + 1];

        // Calculate realtive position
        float relativeZ = fmod(seg.worldZ - camera.z, trackLength);
        float nextRelativeZ = fmod(nextSeg.worldZ - camera.z, trackLength);

        // Skip if behind camera
        if (relativeZ < 0.1f) continue;

        // Calculate screen positions
        float screenY = horizonY + (camera.y / relativeZ) * camera.fov;
        float nextScreenY = horizonY + (camera.y / nextRelativeZ) * camera.fov;

        // Calculate strip dimensions
        float stripHeight = nextScreenY - screenY;
        float stripWidth = -(camera.y / relativeZ) * camera.fov * 2.0f;

        SDL_SetRenderDrawColor(renderer, 100, static_cast<int>(i) * 255 / NUM_SEGMENTS, 100, 255);

        SDL_Rect strip;
        strip.x = static_cast<int>((SCREEN_WIDTH - static_cast<int>(stripWidth)) / 2);
        strip.y = static_cast<int>(screenY);
        strip.w = static_cast<int>(stripWidth);
        strip.h = static_cast<int>(stripHeight);

        SDL_RenderFillRect(renderer, &strip);
    }
}