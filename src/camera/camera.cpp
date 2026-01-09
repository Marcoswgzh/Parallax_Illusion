#include "camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../delta_time.hpp"
#include "../mouse.hpp"
#include "projection.hpp"

static float clamp_value(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

Camera::Camera() {
    this->cameraPosition = CENTER_POSITION;
}

void Camera::update_position_from_face(const Gaze& gaze, float faceWidth) {
    float targetX = gaze.x * MOVEMENT_SCALE_X;
    float targetY = gaze.y * MOVEMENT_SCALE_Y;

    float compensatedWidth = faceWidth * (1.0f + (abs(gaze.x) * 0.5f));
    float widthDiff = compensatedWidth - REFERENCE_FACE_WIDTH;
    float targetZ = CENTER_POSITION.z + (widthDiff * DEPTH_SENSITIVITY);

    this->cameraPosition.x = interpolate(this->cameraPosition.x, targetX, SMOOTHING_FACTOR);
    this->cameraPosition.y = interpolate(this->cameraPosition.y, targetY, SMOOTHING_FACTOR);
    this->cameraPosition.z = interpolate(this->cameraPosition.z, targetZ, SMOOTHING_FACTOR);
}

Gaze Camera::compute_gaze_from_face(cv::Rect face, int columns, int rows) {
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

float Camera::interpolate(float a, float b, float t) { return a + (b - a) * t; }

void Camera::view() {
    glm::vec3 target = this->cameraPosition +  glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(this->cameraPosition, target, this->cameraUp);
    Projector* projector = Projector::get_instance();
    projector->set_view_projection(view);
}
