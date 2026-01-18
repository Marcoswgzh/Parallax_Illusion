#include "surface.hpp"

#include <glm/glm.hpp>

Surface::Surface(vector<float> vertices, int n_triangles, glm::vec2 position) {
    this->vertices = vertices;
    this->n_triangles = n_triangles;
    this->position = position;
}

vector<float>* Surface::get_vertices() { return &this->vertices; }

int Surface::get_n_triangles() { return this->n_triangles; }

glm::vec2 Surface::get_position() { return this->position; }
