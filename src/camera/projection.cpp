#include "projection.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "../render/renderer.hpp"
#include "../window_manager.hpp"
using namespace std;

Projector* Projector::instance = nullptr;

Projector* Projector::get_instance() {
    if (instance == nullptr) {
        instance = new Projector();
    }
    return instance;
}

/**
 * Constructs the projector.
 */
Projector::Projector() {}

void Projector::set_view_projection(glm::mat4 view) {
    // Get the width and height from the viewport
    int width, height;
    glfwGetFramebufferSize(WindowManager::get_instance()->get_window(), &width, &height);

    this->projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    this->view_projection = this->projection * view;
}

vector<float> Projector::project(Mesh mesh, int offset) {
    vector<float> projected_vertices;
    projected_vertices.reserve(18 * mesh.get_n_triangles());

    int stride = 3 + offset;

    for (int i = 0; i < 18 * mesh.get_n_triangles() / stride; i++) {
        glm::vec4 projected =
            this->view_projection * glm::vec4((*mesh.get_vertices())[i * stride] + mesh.get_position().x,
                                              (*mesh.get_vertices())[i * stride + 1] + mesh.get_position().y,
                                              (*mesh.get_vertices())[i * stride + 2] + mesh.get_position().z, 1.0f);

        glm::vec3 normalized_projection = glm::vec3(projected) / projected.w;
        projected_vertices.push_back(normalized_projection.x);
        projected_vertices.push_back(normalized_projection.y);
        projected_vertices.push_back(normalized_projection.z);

        // Loop with offset amount (all none position elements are ignored)
        for (int j = 0; j < offset; j++) {
            projected_vertices.push_back((*mesh.get_vertices())[i * stride + 3 + j]);
        }
    }

    return projected_vertices;
}
