#include "scene_renderer.hpp"

#include <iostream>

#include "../camera/camera.hpp"
#include "../camera/projection.hpp"
#include "../gl.h"
using namespace std;

SceneRenderer* SceneRenderer::instance = nullptr;

SceneRenderer* SceneRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new SceneRenderer();
    }
    return instance;
}

SceneRenderer::SceneRenderer() { this->light_type = LightType::Phong; }

void SceneRenderer::update_colored_mesh(Mesh mesh) {
    // Use shader before setting uniforms
    this->color_shader.use();
    this->color_shader.set_mat4("projection", Projector::get_instance()->get_view_projection());
    this->color_shader.set_vec3("camera_position", this->camera.get_camera_position());
    this->color_shader.set_int("light_type", this->light_type);

    // Prepare/get data for the buffers
    vector<float> positioned_vertices = mesh.get_positioned_vertices(3);
    vector<int> indices = *mesh.get_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positioned_vertices.size() * sizeof(float), positioned_vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SceneRenderer::update_textured_mesh(Mesh mesh) {
    // Use shader before setting uniforms
    this->texture_shader.use();
    this->texture_shader.set_mat4("projection", Projector::get_instance()->get_view_projection());
    this->texture_shader.set_vec3("camera_position", this->camera.get_camera_position());
    this->texture_shader.set_int("light_type", this->light_type);

    // Prepare/get data for the buffers
    vector<float> positioned_vertices = mesh.get_positioned_vertices(2);
    vector<int> indices = *mesh.get_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Three points per triangle * stride
    glBufferData(GL_ARRAY_BUFFER, positioned_vertices.size() * sizeof(float), positioned_vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh.get_texture().value().get_textureID());

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SceneRenderer::update() {
    // Update all the meshes
    for (Mesh mesh : this->meshes) {
        // Use different update method depending on whether the mesh has a texture or not
        if (mesh.get_texture().has_value()) {
            this->update_textured_mesh(mesh);
        } else {
            this->update_colored_mesh(mesh);
        }

        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->n_triangles * 3, GL_UNSIGNED_INT, 0);
    }
}

void SceneRenderer::draw() {
    // Update the camera before the draw
    this->camera.update();

    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    this->update();
}

int SceneRenderer::add(Mesh mesh) {
    // Update the total amount of triangles and number of visual objects
    this->n_triangles += mesh.get_n_triangles();

    // Add the triangles from the current object to the triangles vector
    this->meshes.push_back(mesh);

    // Return the index of the added item (for later control of the visual
    // object)
    return this->meshes.size();
}

void SceneRenderer::remove(int index, int n_triangles) {
    // Update the total amount of triangles and number of visual objects
    this->n_triangles -= n_triangles;

    // Remove the visual object
    // TODO: Make sure this indexing is correct
    this->meshes.erase(this->meshes.begin() + index);
}

void SceneRenderer::set_light_type(LightType type) { this->light_type = type; }

void SceneRenderer::toggle_movement() {
    this->camera.toggle_movement();
}

void SceneRenderer::toggle_key_movement() {
    this->camera.toggle_key_movement();
}

void SceneRenderer::remove_current_scene() {
    this->meshes.clear();
    this->n_triangles = 0;
    this->light_type = LightType::Phong;

    // TODO: RESET CAMERA
}