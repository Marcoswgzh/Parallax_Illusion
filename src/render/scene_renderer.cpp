#include "scene_renderer.hpp"

#include <iostream>

#include "../camera/projection.hpp"
#include "../gl.h"
#include "renderer.hpp"
using namespace std;

SceneRenderer* SceneRenderer::instance = nullptr;

SceneRenderer* SceneRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new SceneRenderer();
    }
    return instance;
}

SceneRenderer::SceneRenderer() {}

void SceneRenderer::update_mesh(Mesh mesh) {
    // TODO: Use correct shader
    // Use the shader before setting values
    this->shader.use();
    Projector* projector = Projector::get_instance();
    this->shader.set_mat4("projection", projector->get_view_projection());
    vector<int> flattened_indices = *mesh.get_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 18 * sizeof(float), mesh.get_positioned_vertices().data(),
                 GL_DYNAMIC_DRAW);

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

void SceneRenderer::update() {
    // Update all the meshes
    for (Mesh mesh : this->meshes) {
        this->update_mesh(mesh);
    }
}

vector<int> SceneRenderer::get_flattened_indices() {
    vector<int> flattened;
    flattened.reserve(this->n_triangles * 3);
    int offset = 0;
    for (Mesh mesh : this->meshes) {
        for (int index : *mesh.get_indices()) {
            flattened.push_back(index + offset);
        }

        // Add the amount of triangles to adjust the indices of the future meshes
        offset += (int)(mesh.get_vertices()->size() / 6);
    }

    return flattened;
}

void SceneRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    // TODO: Track position/angle changes in the camera, so we only have to render
    // if the result will be different For now always rerender a 3D scene
    this->update();

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->n_triangles * 3, GL_UNSIGNED_INT, 0);
}