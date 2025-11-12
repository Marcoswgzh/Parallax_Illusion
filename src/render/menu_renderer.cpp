#include "menu_renderer.hpp"

#include <iostream>

#include "../gl.h"
#include "renderer.hpp"
using namespace std;

MenuRenderer* MenuRenderer::instance = nullptr;

// TODO: One scene renderer for each window (so create a vector of instances
// instead)
MenuRenderer* MenuRenderer::get_instance(GLFWwindow* window) {
    if (instance == nullptr) {
        instance = new MenuRenderer(window);
    }
    return instance;
}

MenuRenderer::MenuRenderer(GLFWwindow* window) { this->window = window; }

void MenuRenderer::update() {
    vector<float> flattened = this->get_flattened();

    glGenVertexArrays(RenderGroups::Menu, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(RenderGroups::Menu, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 15 * sizeof(float), flattened.data(), GL_STATIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Change has been handled, so reset state
    this->change = false;
}

vector<float> MenuRenderer::get_flattened() {
    // First flatten the triangle data
    vector<float> flattened;
    flattened.reserve(this->n_triangles * 15);

    for (VisualObject object : this->visual_objects) {
        flattened.insert(flattened.end(), object.triangles.begin(), object.triangles.end());
    }

    return flattened;
}

void MenuRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    // Make sure to use the correct shaders
    this->shader.use();

    // Only update when a change has happened
    if (this->change) {
        this->update();
    }

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->n_triangles * 3);
}