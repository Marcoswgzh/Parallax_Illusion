#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>

#include "../gaze/gaze.hpp"

// Camera state
extern glm::vec3 cameraPosition;
extern glm::vec3 cameraViewOffset;

// Initialize camera with optional position
void init_camera(float x = 0.f, float y = 0.5f, float z = -3.f);

// Update camera position from input (WASD/Space/Shift)
void update_camera_input(float dx, float dy, float dz);

// Update camera gaze offset
void update_camera_gaze(const Gaze& gaze, float gazeScaleX, float gazeScaleY, float smoothing);

// Reset gaze offset to default
void reset_camera_gaze(float smoothing);

// Get camera position
glm::vec3 get_camera_position();

// Get camera target (position + forward + gaze offset)
glm::vec3 get_camera_target();

#endif
