#include "../gl.h"
#include "menu_renderer.hpp"

MenuRenderer* MenuRenderer::instance = nullptr;

MenuRenderer* MenuRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new MenuRenderer();
    }

    return instance;
}

MenuRenderer::MenuRenderer() {}

void MenuRenderer::update_surface(Surface* surface, int offset) {
    // Bind VBO and VAO
    glGenVertexArrays(1, &surface->VAO);
    glBindVertexArray(surface->VAO);
    glGenBuffers(1, &surface->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, surface->VBO);

    // Load vertices into the buffers
    vector<float> vertices = *surface->get_vertices();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (2 + offset) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (2 + offset) * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    surface->set_loaded(true);
}

void MenuRenderer::update_color_surface(Surface* surface) {
    // Make sure to use the shaders before setting uniforms
    this->color_shader.use();
    this->color_shader.set_int("z_level", surface->get_z_level());

    // Only load surface again if it's not loaded yet
    if (!surface->is_loaded()) {
        this->update_surface(surface, 3);
    }
}

void MenuRenderer::update_texture_surface(Surface* surface) {
    // Make sure to use the shaders before setting uniforms
    this->texture_shader.use();
    this->texture_shader.set_int("z_level", surface->get_z_level());

    // Only load surface again if it's not loaded yet
    if (!surface->is_loaded()) {
        this->update_surface(surface, 2);
    }

    glBindVertexArray(surface->VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, surface->get_texture().value().get_textureID());
}

void MenuRenderer::update() {
    for (Surface& surface : this->surfaces) {
        // Don't display surfaces which shouldn't be displayed
        if (!surface.should_display()) {
            continue;
        }

        // Use different update method depending on whether the surface has a texture or not
        if (surface.get_texture().has_value()) {
            this->update_texture_surface(&surface);
        } else {
            this->update_color_surface(&surface);
        }

        glBindVertexArray(surface.VAO);
        glDrawArrays(GL_TRIANGLES, 0, surface.get_n_triangles() * 3);
        glBindVertexArray(0);
    }
}

int MenuRenderer::add(Surface surface) {
    // Update the total amount of triangles and number of visual objects
    this->n_triangles += surface.get_n_triangles();

    // Add the triangles from the current object to the triangles vector
    this->surfaces.push_back(surface);

    // Return the index of the added item (for later control of the mesh)
    return this->surfaces.size();
}

void MenuRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    this->update();
}

Surface* MenuRenderer::get_surface(int index) {
    return &this->surfaces.at(index);
}
