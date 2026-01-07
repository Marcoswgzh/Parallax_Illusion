#include "menu_renderer.hpp"

#include <iostream>

#include "../gl.h"
#include "renderer.hpp"
using namespace std;

MenuRenderer* MenuRenderer::instance = nullptr;

// TODO: One scene renderer for each window (so create a vector of instances
// instead)
MenuRenderer* MenuRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new MenuRenderer();
    }
    return instance;
}

MenuRenderer::MenuRenderer() {}

void MenuRenderer::update() {
    vector<float> flattened = this->get_flattened_vertices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
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

vector<float> MenuRenderer::get_flattened_vertices() {
    // First flatten the triangle data
    vector<float> flattened;
    flattened.reserve(this->n_triangles * 15);

    for (Mesh mesh : this->meshes) {
        flattened.insert(flattened.end(), (*mesh.get_vertices()).begin(), (*mesh.get_vertices()).end());
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