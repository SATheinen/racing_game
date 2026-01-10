#include <Road.h>

Road::Road(int SegmentHeight, int SegmentWidth, int SegmentLength, int TrackLength, float HorizonY)
    : segmentHeight(segmentHeight), segmentWidth(SegmentHeight), segmentLength(SegmentLength),
    trackLength(TrackLength), horizonY(HorizonY) {}

void Road::update(Uint32 deltaTime, float cameraZ) {
    if (cameraZ > TRACK_LENGTH / 1.0f) {
        cameraZ -= TRACK_LENGTH / 1.0f;
    }

    for (int i = 0; i < NUM_SEGMENTS - 1; i++) {
        float segmentWorldZ = i * SEGMENT_LENGTH;
        float relativeZ = segmentWorldZ - cameraZ;

        if (relativeZ <= 0.1f) continue;

        float screenY = horizonY + (FOV / relativeZ);
        
        // next segments position
        float nextRelativeZ = relativeZ + SEGMENT_LENGTH;
        float nextScreenY = horizonY + (FOV / nextRelativeZ);

        float stripHeight = nextScreenY - screenY;
        float stripWidth = segmentWidth / relativeZ;
    }
}

void Road::render(SDL_Renderer* renderer) {
    if (i % 2 == 0){
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    } else {
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    }

    SDL_Rect strip;
    strip.x = static_cast<int>((SCREEN_WIDTH - stripWidth) / 2);
    strip.y = static_cast<int>(screenY);
    strip.w = static_cast<int>(stripWidth);
    strip.h = static_cast<int>(stripHeight);

    SDL_RenderFillRect(renderer, &strip);
}