#pragma once

// Screen dimensions
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

// Rendering constants
const float HORIZON_Y = 320.0f;
const float CAMERA_HEIGHT = 300.0f;
const float FOV = 2.0f;

// Track constants
const int NUM_SEGMENTS = 4000;
const float SEGMENT_LENGTH = 0.1f;
const float TRACK_LENGTH = SEGMENT_LENGTH * static_cast<float>(NUM_SEGMENTS);