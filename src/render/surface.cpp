#include <glm/glm.hpp>

#include "surface.hpp"

/**
 * Overloaded surface constructor to allow colored surfaces. A surface holds all information about a 2D object. 
 */
Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->z_level = z_level;
}

/**
 * Overloaded surface constructor to allow textured surfaces. A surface holds all information about a 2D object. 
 */
Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level, Texture texture) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->z_level = z_level;
    this->texture = std::make_optional(texture);
}

/**
 * Gets the vertices.
 */
vector<float>* Surface::get_vertices() { return &this->vertices; }

/**
 * Gets the number of triangles in the surface.
 */
int Surface::get_n_triangles() { return this->n_triangles; }

/**
 * Gets the surface position.
 */
glm::vec2 Surface::get_position() { return this->position; }

/**
 * Gets the surface z-level.
 */
int Surface::get_z_level() {
    return this->z_level;
}

/**
 * Gets if the surface should be displayed.
 */
bool Surface::should_display() {
    return this->display;
}

/**
 * Optionally gets the texture of the surface.
 */
std::optional<Texture> Surface::get_texture() {
    return this->texture;
}

/**
 * Gets if the surface is already loaded into a buffer.
 */
bool Surface::is_loaded() {
    return this->loaded;
}

/**
 * Sets the surfaces loaded status.
 */
void Surface::set_loaded(bool status) {
    this->loaded = status;
}

/**
 * Toggles the display of a surface.
 */
void Surface::toggle_display() {
    this->display = !this->display;
}
