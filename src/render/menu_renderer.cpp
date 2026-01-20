#include "menu_renderer.hpp"

#include <iostream>

#include "../gl.h"
using namespace std;

MenuRenderer* MenuRenderer::instance = nullptr;

MenuRenderer* MenuRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new MenuRenderer();
    }
    return instance;
}

MenuRenderer::MenuRenderer() {}

void MenuRenderer::update_color_surface(Surface surface) {
    // Don't display surfaces which shouldn't be displayed
    if (!surface.should_display()) {
        return;
    }

    // Make sure to use the shaders before setting uniforms
    this->color_shader.use();
    this->color_shader.set_int("z_level", surface.get_z_level());

    vector<float> vertices = *surface.get_vertices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->n_triangles * 3);
}

void MenuRenderer::update_texture_surface(Surface surface) {
    // Don't display surfaces which shouldn't be displayed
    if (!surface.should_display()) {
        return;
    }

    // Make sure to use the shaders before setting uniforms
    this->texture_shader.use();
    this->texture_shader.set_int("z_level", surface.get_z_level());

    vector<float> vertices = *surface.get_vertices();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, surface.get_texture().value().get_textureID());

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->n_triangles * 3);
}

void MenuRenderer::update() {
    for (Surface surface : this->surfaces) {
        // Use different update method depending on whether the surface has a texture or not
        if (surface.get_texture().has_value()) {
            this->update_texture_surface(surface);
        } else {
            this->update_color_surface(surface);
        }
    }
}

vector<float> MenuRenderer::get_flattened_vertices() {
    // First flatten the triangle data
    vector<float> flattened;
    flattened.reserve(this->n_triangles * 15);

    for (Surface surface : this->surfaces) {
        flattened.insert(flattened.end(), (*surface.get_vertices()).begin(), (*surface.get_vertices()).end());
    }

    return flattened;
}

int MenuRenderer::add(Surface surface) {
    // Update the total amount of triangles and number of visual objects
    this->n_triangles += surface.get_n_triangles();

    // Add the triangles from the current object to the triangles vector
    this->surfaces.push_back(surface);

    // Return the index of the added item (for later control of the mesh)
    return this->surfaces.size();
}

Surface* MenuRenderer::get_surface(int index) {
    return &this->surfaces.at(index);
}

void MenuRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    this->update();
}

