#include "scene_renderer.hpp"

#include <iostream>

#include "../camera/camera.hpp"
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

SceneRenderer::SceneRenderer() { this->light_type = LightType::Phong; }

void SceneRenderer::update_colored_mesh(Mesh mesh) {
    // Use shader before setting uniforms
    this->color_shader.use();
    this->color_shader.set_mat4("projection", Projector::get_instance()->get_view_projection());
    this->color_shader.set_vec3("camera_position", this->camera.get_camera_position());
    this->color_shader.set_int("light_type", this->light_type);
    vector<int> indices = *mesh.get_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 18 * sizeof(float), mesh.get_positioned_vertices().data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->n_triangles * 3 * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

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

void SceneRenderer::update_textured_mesh(Mesh mesh) {
    // Use shader before setting uniforms
    this->texture_shader.use();
    this->texture_shader.set_mat4("projection", Projector::get_instance()->get_view_projection());
    this->texture_shader.set_vec3("camera_position", this->camera.get_camera_position());
    this->texture_shader.set_int("light_type", this->light_type);
    vector<int> indices = *mesh.get_indices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Three points per triangle * stride
    glBufferData(GL_ARRAY_BUFFER, mesh.get_positioned_vertices().size() * sizeof(float), mesh.get_positioned_vertices().data(), GL_DYNAMIC_DRAW);

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

    this->change = false;
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

    // TODO: Track position/angle changes in the camera, so we only have to render
    // if the result will be different For now always rerender a 3D scene
    this->update();
}

void SceneRenderer::set_light_type(LightType type) { this->light_type = type; }