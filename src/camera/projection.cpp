#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../window_manager.hpp"
#include "projection.hpp"

Projector* Projector::instance = nullptr;

/**
 * Gets the single projector instance.
 */
Projector* Projector::get_instance() {
    if (instance == nullptr) {
        instance = new Projector();
    }

    return instance;
}

/**
 * Constructs the projector. The projector wraps around the projection calculations.
 */
Projector::Projector() {}

void Projector::set_view_projection(glm::mat4 view) {
    // Get the width and height from the viewport
    int width, height;
    glfwGetFramebufferSize(WindowManager::get_instance()->get_window(), &width, &height);

    this->projection = glm::perspective(glm::radians(this->fov), (float)width / (float)height, 0.1f, 100.0f);
    this->view_projection = this->projection * view;
}

glm::mat4 Projector::get_view_projection() { return this->view_projection; }
