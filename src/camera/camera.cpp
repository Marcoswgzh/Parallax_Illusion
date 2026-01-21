#include <glm/ext/matrix_transform.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

#include "camera.hpp"
#include "../delta_time.hpp"
#include "../mouse.hpp"
#include "../window_manager.hpp"
#include "projection.hpp"
#include "../detection/recording.hpp"

Camera::Camera() {
    this->reset();
}

void Camera::reset() {
    this->yaw = 90.0f;
    this->pitch = 0.0f;
    this->camera_position = glm::vec3(0.f, 0.5f, -3.f);
    this->camera_front = glm::vec3(0.f, 0.f, 1.0f);
}

/// Updates the camera according to all active movement types (key, mouse and tracking-based).
void Camera::update() {
    if (!this->movement) {
        return;
    }

    if (this->key_movement) {
        // Process key input
        this->process_input();

        // Update the view based on mouse input
        this->update_mouse_view();
    }

    // Process recorder input and update the camera position accordingly
    this->update_recorder_view();

    // Compute the new camera view
    this->set_view();
}

void Camera::process_input() {
    GLFWwindow* window = WindowManager::get_instance()->get_window();

    // WASD + vertical (shift and space)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) this->move_forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) this->move_backward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) this->move_left();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) this->move_right();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) this->move_up();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) this->move_down();
}

void Camera::update_mouse_view() {
    Mouse* mouse = Mouse::get_instance();

    yaw += mouse->x_delta * this->get_sensitivity();
    pitch -= mouse->y_delta * this->get_sensitivity();

    // Bounds for pitch to prevent view from flipping
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    // Calculate a direction vector based on yaw and pitch
    glm::vec3 direction(
        cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    );
    this->camera_front = glm::normalize(direction);

    // Reset the mouse deltas
    mouse->x_delta = 0;
    mouse->y_delta = 0;
}

void Camera::update_recorder_view() {
    Recorder* recorder = Recorder::get_instance();
    recorder->update();

    this->camera_position -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * recorder->get_speed().x * 20.0f;
    this->camera_position -= this->camera_up * recorder->get_speed().y * 20.0f;
    this->camera_position += this->camera_front * recorder->get_speed().z * 80.0f;
    recorder->reset_deltas();
}

void Camera::set_view() {
    // Compute and set the view matrix
    glm::mat4 view = glm::lookAt(this->camera_position, this->camera_position + this->camera_front, this->camera_up);
    Projector* projector = Projector::get_instance();
    projector->set_view_projection(view);
}

// Key-based movement
void Camera::move_forward() {
    this->camera_position += this->camera_front * this->get_speed();
}

void Camera::move_backward() {
    this->camera_position -= this->camera_front * this->get_speed();
}

void Camera::move_up() { 
    this->camera_position += this->get_speed() * this->camera_up;
}

void Camera::move_down() {
    this->camera_position -= this->get_speed() * this->camera_up;
}

void Camera::move_left() {
    this->camera_position -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->get_speed();
}

void Camera::move_right() {
    this->camera_position += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * this->get_speed();
}

/// Gets the cameras key-based speed (taking delta time into account, should also be used internally).
float Camera::get_speed() {
    return this->speed * DeltaTime::get_instance()->get_delta_time();
}

/// Gets the cameras mouse-based sensitivity (taking delta time into account, should also be used internally).
float Camera::get_sensitivity() {
    return this->sensitivity * DeltaTime::get_instance()->get_delta_time();
}

/// Gets the camera position
glm::vec3 Camera::get_camera_position() {
    return this->camera_position;
}

void Camera::toggle_key_movement() {
    this->key_movement = !this->key_movement;
}

void Camera::toggle_movement() {
    this->movement = !this->movement;
}
