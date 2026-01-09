#include "mesh.hpp"

#include <glm/glm.hpp>

Mesh::Mesh(vector<float> vertices, vector<int> indices, int n_triangles, glm::vec3 position, std::optional<Texture> texture) {
    this->vertices = vertices;
    this->indices = indices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->texture = texture;
}

vector<float>* Mesh::get_vertices() {
    return &this->vertices;
}

vector<int>* Mesh::get_indices() {
    return &this->indices;
}

int Mesh::get_n_triangles() {
    return this->n_triangles;
}

glm::vec3 Mesh::get_position() {
    return this->position;
}

std::optional<Texture> Mesh::get_texture() {
    return this->texture;
}