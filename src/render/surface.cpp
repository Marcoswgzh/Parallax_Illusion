#include <glm/glm.hpp>

#include "surface.hpp"

Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->z_level = z_level;
}

Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level, Texture texture) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->z_level = z_level;
    this->texture = std::make_optional(texture);
}

vector<float>* Surface::get_vertices() { return &this->vertices; }

int Surface::get_n_triangles() { return this->n_triangles; }

glm::vec2 Surface::get_position() { return this->position; }

int Surface::get_z_level() {
    return this->z_level;
}

bool Surface::should_display() {
    return this->display;
}

std::optional<Texture> Surface::get_texture() {
    return this->texture;
}

bool Surface::is_loaded() {
    return this->loaded;
}

void Surface::set_loaded(bool status) {
    this->loaded = status;
}

void Surface::toggle_display() {
    this->display = !this->display;
}
