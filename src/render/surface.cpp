#include <glm/glm.hpp>
#include <iostream>

#include "surface.hpp"

Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->z_level = z_level;
}

vector<float>* Surface::get_vertices() { return &this->vertices; }

int Surface::get_n_triangles() { return this->n_triangles; }

glm::vec2 Surface::get_position() { return this->position; }

int Surface::get_z_level() {
    return this->z_level;
}

void Surface::toggle_display() {
    this->display = !this->display;
}

bool Surface::should_display() {
    return this->display;
}