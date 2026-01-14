#include "camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../delta_time.hpp"
#include "../mouse.hpp"
#include "../window_manager.hpp"
#include "projection.hpp"

static float clamp_value(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

Camera::Camera() {
    this->camera_position = glm::vec3(0.f, 0.5f, -3.f);
    this->camera_front = glm::vec3(0.f, 0.f, 1.0f);
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
    camera_front.x = interpolate(camera_front.x, gaze.x * gazeScaleX, smoothing);
    camera_front.y = interpolate(camera_front.y, gaze.y * gazeScaleY, smoothing);
    camera_front.z = interpolate(camera_front.z, 0.f, smoothing);
}

float Camera::interpolate(float a, float b, float t) { return a + (b - a) * t; }

void Camera::move_forward() { this->camera_position += this->camera_front * this->get_speed(); }
void Camera::move_backward() { this->camera_position -= this->camera_front * this->get_speed(); }
void Camera::move_left() {
    this->camera_position -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->get_speed();
}

void Camera::move_right() {
    this->camera_position += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->get_speed();
}

void Camera::move_up() { this->camera_position += this->get_speed() * this->camera_up; }
void Camera::move_down() { this->camera_position -= this->get_speed() * this->camera_up; }

void Camera::view() {
    // Compute and set the view matrix
    glm::mat4 view = glm::lookAt(this->camera_position, this->camera_position + this->camera_front, this->camera_up);
    Projector* projector = Projector::get_instance();
    projector->set_view_projection(view);
}

void Camera::update_mouse_view() {
    Mouse* mouse = Mouse::get_instance();

    yaw += mouse->x_delta * this->get_sensitivity();
    pitch -= mouse->y_delta * this->get_sensitivity();

    // Bounds for pitch to prevent view from flipping
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->camera_front = glm::normalize(direction);

    // Reset the mouse deltas
    mouse->x_delta = 0;
    mouse->y_delta = 0;
}

float Camera::get_speed() { return this->speed * DeltaTime::get_instance()->get_delta_time(); }

float Camera::get_sensitivity() { return this->sensitivity * DeltaTime::get_instance()->get_delta_time(); }

glm::vec3 Camera::get_camera_position() { return this->camera_position; }

void Camera::process_input() {
    GLFWwindow* window = WindowManager::get_instance()->get_window();

    // WASD + vertical
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) this->move_forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) this->move_backward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) this->move_left();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) this->move_right();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) this->move_up();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) this->move_down();
}

void Camera::update() {
    // Process key input
    this->process_input();

    // Update the view based on mouse input
    this->update_mouse_view();

    // TODO: Process recorder input

    // Compute the new camera view
    this->view();
}