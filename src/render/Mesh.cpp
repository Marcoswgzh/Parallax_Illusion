#include "mesh.hpp"

#include <glm/glm.hpp>

Mesh::Mesh(vector<float> vertices, vector<int> indices, int n_triangles, glm::vec3 position) {
    this->vertices = vertices;
    this->indices = indices;
    this->n_triangles = n_triangles;
    this->position = position;
}

vector<float>* Mesh::get_vertices() { return &this->vertices; }

vector<int>* Mesh::get_indices() { return &this->indices; }

int Mesh::get_n_triangles() { return this->n_triangles; }

glm::vec3 Mesh::get_position() { return this->position; }