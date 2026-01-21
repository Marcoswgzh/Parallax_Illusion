#include "../gl.h"
#include "menu_renderer.hpp"

MenuRenderer* MenuRenderer::instance = nullptr;

/**
 * Gets the single menu renderer instance.
 */
MenuRenderer* MenuRenderer::get_instance() {
    if (instance == nullptr) {
        instance = new MenuRenderer();
    }

    return instance;
}

/**
 * Menu renderer constructor. The menu renderer handles all 2D rendering. It holds all the created surfaces.
 */
MenuRenderer::MenuRenderer() {}

/**
 * Loads a single surface into a buffer. This only has to be done once and only has to be done 
 * again if the position or shape of the surface has changed.
 */
void MenuRenderer::update_surface(Surface* surface, int offset) {
    // Bind VBO and VAO
    glGenVertexArrays(1, surface->get_vao());
    glBindVertexArray(*surface->get_vao());
    glGenBuffers(1, surface->get_vbo());
    glBindBuffer(GL_ARRAY_BUFFER, *surface->get_vbo());

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

/**
 * Updates a colored surface. It only loads a surface if it hasn't been loaded before.
 * It does always update the shaders.
 */
void MenuRenderer::update_color_surface(Surface* surface) {
    // Make sure to use the shaders before setting uniforms
    this->color_shader.use();
    this->color_shader.set_int("z_level", surface->get_z_level());

    // Only load surface again if it's not loaded yet
    if (!surface->is_loaded()) {
        this->update_surface(surface, 3);
    }
}

/**
 * Updates a textured surface. It only loads a surface if it hasn't been loaded before.
 * It does always update the shaders.
 */
void MenuRenderer::update_texture_surface(Surface* surface) {
    // Make sure to use the shaders before setting uniforms
    this->texture_shader.use();
    this->texture_shader.set_int("z_level", surface->get_z_level());

    // Only load surface again if it's not loaded yet
    if (!surface->is_loaded()) {
        this->update_surface(surface, 2);
    }

    glBindVertexArray(*surface->get_vao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, surface->get_texture().value().get_texture_id());
}

/**
 * Iterates over all the surfaces and updates them. It skips the ones which should not be displayed.
 * It also decides between using colored or textured rendering.
 */
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

        glBindVertexArray(*surface.get_vao());
        glDrawArrays(GL_TRIANGLES, 0, surface.get_n_triangles() * 3);
        glBindVertexArray(0);
    }
}

/**
 * Adds a surface to the menu renderer. It returns the size after adding so the surface can be retrieved with its index.
 */
int MenuRenderer::add(Surface surface) {
    // Update the total amount of triangles and number of visual objects
    this->n_triangles += surface.get_n_triangles();

    // Add the triangles from the current object to the triangles vector
    this->surfaces.push_back(surface);

    // Return the index of the added item (for later control of the surface)
    return this->surfaces.size();
}

/**
 * Simple wrapper method to draw all the 2D surfaces.
 */
void MenuRenderer::draw() {
    // Don't execute if there is nothing to draw
    if (this->n_triangles <= 0) {
        return;
    }

    this->update();
}

/**
 * Gets a surface by id.
 */
Surface* MenuRenderer::get_surface(int index) {
    return &this->surfaces.at(index);
}
