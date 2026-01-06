#include "Mesh.hpp"

Mesh::Mesh(vector<float> triangles, vector<int> indices, int n_triangles) {
    this->triangles = triangles;
    this->indices = indices;
    this->n_triangles = n_triangles;
}

vector<float>* Mesh::get_triangles() { return &this->triangles; }

vector<int>* Mesh::get_indices() { return &this->indices; }

int Mesh::get_n_triangles() { return this->n_triangles; }