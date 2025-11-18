#include "camera.hpp"

static float interpolate(float a, float b, float t) {
    return a + (b - a) * t;
}

// Camera globals
glm::vec3 cameraPosition(0.f, 0.5f, -3.f);
glm::vec3 cameraViewOffset(0.f, 0.f, 0.f);

void init_camera(float x, float y, float z) {
    cameraPosition = glm::vec3(x, y, z);
    cameraViewOffset = glm::vec3(0.f, 0.f, 0.f);
}

void update_camera_input(float dx, float dy, float dz) {
    cameraPosition += glm::vec3(dx, dy, dz);
}

void update_camera_gaze(const Gaze &gaze, float gazeScaleX, float gazeScaleY, float smoothing) {
    if (!gaze.valid) return;
    cameraViewOffset.x = interpolate(cameraViewOffset.x, gaze.x * gazeScaleX, smoothing);
    cameraViewOffset.y = interpolate(cameraViewOffset.y, gaze.y * gazeScaleY, smoothing);
    cameraViewOffset.z = interpolate(cameraViewOffset.z, 0.f, smoothing);
}


void reset_camera_gaze(float smoothing) {
    //cameraViewOffset.x = interpolate(cameraViewOffset.x, 0.f, smoothing);
    //cameraViewOffset.y = interpolate(cameraViewOffset.y, 0.f, smoothing);
    //cameraViewOffset.z = interpolate(cameraViewOffset.z, 0.f, smoothing);
}

glm::vec3 get_camera_position() {
    return cameraPosition;
}

glm::vec3 get_camera_target() {
    // Look forward along +Z axis plus gaze/parallax offset
    return cameraPosition + glm::vec3(cameraViewOffset.x, cameraViewOffset.y, 1.f + cameraViewOffset.z);
}
