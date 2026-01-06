#include "camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../mouse.hpp"
#include "projection.hpp"

static float clamp_value(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

Camera::Camera() {
    this->cameraPosition = glm::vec3(0.f, 0.5f, -3.f);
    this->cameraFront = glm::vec3(0.f, 0.f, 1.0f);
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
    return;  // TODO: Ignoring updating camera gaze, because it doesn't work propperly
    cameraFront.x = interpolate(cameraFront.x, gaze.x * gazeScaleX, smoothing);
    cameraFront.y = interpolate(cameraFront.y, gaze.y * gazeScaleY, smoothing);
    cameraFront.z = interpolate(cameraFront.z, 0.f, smoothing);
}

float Camera::interpolate(float a, float b, float t) { return a + (b - a) * t; }

void Camera::move_forward() { this->cameraPosition += this->cameraFront * this->speed; }
void Camera::move_backward() { this->cameraPosition -= this->cameraFront * this->speed; }
void Camera::move_left() {
    this->cameraPosition -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->speed;
}

void Camera::move_right() {
    this->cameraPosition += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->speed;
}

void Camera::move_up() { this->cameraPosition += this->speed * this->cameraUp; }
void Camera::move_down() { this->cameraPosition -= this->speed * this->cameraUp; }

void Camera::view() {
    // Compute view matrix
    glm::mat4 view = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);

    Projector* projector = Projector::get_instance();
    projector->set_view_projection(view);
}

void Camera::update_mouse_view() {
    Mouse* mouse = Mouse::get_instance();

    yaw += mouse->x_delta * this->sensitivity;
    pitch -= mouse->y_delta * this->sensitivity;

    // Bounds for pitch to prevent view from flipping
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->cameraFront = glm::normalize(direction);

    // Reset the mouse deltas
    mouse->x_delta = 0;
    mouse->y_delta = 0;
}