#include "scene_renderer.hpp"

#include <iostream>

#include "../gl.h"
#include "../scene/projection.hpp"
#include "renderer.hpp"
using namespace std;

SceneRenderer* SceneRenderer::instance = nullptr;

// TODO: One scene renderer for each window (so create a vector of instances
// instead)
SceneRenderer* SceneRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new SceneRenderer();
    }
    return instance;
}

SceneRenderer::SceneRenderer() {}

void SceneRenderer::update() {
    Projector* projector = Projector::get_instance();
    vector<float> projected = projector->project_list(this->meshes, this->n_triangles);
    vector<int> flattened_indices = this->get_flattened_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 18 * sizeof(float), projected.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->n_triangles * 3 * sizeof(unsigned int), flattened_indices.data(),
                 GL_DYNAMIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->change = false;
}

vector<int> SceneRenderer::get_flattened_indices() {
    vector<int> flattened;
    flattened.reserve(this->n_triangles * 3);
    for (Mesh mesh : this->meshes) {
        vector<int>::iterator indices_start = (*mesh.get_indices()).begin();
        vector<int>::iterator indices_end = (*mesh.get_indices()).end();
        flattened.insert(flattened.end(), indices_start, indices_end);
    }

    return flattened;
}

void SceneRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    // Make sure to use the correct shaders
    this->shader.use();

    // TODO: Track position/angle changes in the camera, so we only have to render
    // if the result will be different For now always rerender a 3D scene
    this->update();

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->n_triangles * 3, GL_UNSIGNED_INT, 0);
}