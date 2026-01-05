#include "camera.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

static float clamp_value(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

Camera::Camera() {
    this->cameraPosition = glm::vec3(0.f, 0.5f, -3.f);
    this->cameraViewOffset = glm::vec3(0.f, 0.f, 0.f);  // TODO: Initializing to zero makes it jitter at the start
}

Gaze Camera::compute_gaze_from_facial(cv::Rect face, int columns, int rows) {
    Gaze result;
    cv::Point face_center(face.x + face.width / 2, face.y + face.height / 2);

    // Use the centre of the face
    float nx = (face_center.x - columns / 2.f) / (columns / 2.f);
    float ny = -(face_center.y - rows / 2.f) / (rows / 2.f);
    // TODO: Maybe remove clamping here?
    result.x = clamp_value(nx, -1.f, 1.f);
    result.y = clamp_value(ny, -1.f, 1.f);
    return result;
}

void Camera::update_camera_gaze(const Gaze& gaze, float gazeScaleX, float gazeScaleY, float smoothing) {
    cameraViewOffset.x = interpolate(cameraViewOffset.x, gaze.x * gazeScaleX, smoothing);
    cameraViewOffset.y = interpolate(cameraViewOffset.y, gaze.y * gazeScaleY, smoothing);
    cameraViewOffset.z = interpolate(cameraViewOffset.z, 0.f, smoothing);
}

float Camera::interpolate(float a, float b, float t) { return a + (b - a) * t; }

glm::vec3 Camera::get_camera_position() { return this->cameraPosition; }

glm::vec3 Camera::get_camera_target() {
    // Look forward along +Z axis plus gaze/parallax offset
    // TODO: Why +1.f on X axis
    return this->cameraPosition +
           glm::vec3(this->cameraViewOffset.x, this->cameraViewOffset.y, 1.f + this->cameraViewOffset.z);
}

float Camera::get_speed() { return this->speed; }

void Camera::move(float dx, float dy, float dz) { this->cameraPosition += glm::vec3(dx, dy, dz); }