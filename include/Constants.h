#pragma once

// Screen dimensions
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

// Rendering constants
const float HORIZON_Y = 320.0f;
const float CAMERA_HEIGHT = 300.0f;
const float FOV = 2.0f;

// Track constants
const int NUM_ROAD_SAMPLES = 4000;
const float SAMPLE_SPACING = 0.1f;
const float VISIBLE_DISTANCE = SAMPLE_SPACING * static_cast<float>(NUM_ROAD_SAMPLES);