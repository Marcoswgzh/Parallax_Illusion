#include "mesh.hpp"

#include <glm/glm.hpp>

Mesh::Mesh(vector<float> vertices, vector<int> indices, int n_triangles, glm::vec3 position,
           std::optional<Texture> texture) {
    this->vertices = vertices;
    this->indices = indices;
    this->n_triangles = n_triangles;
    this->position = position;
    this->texture = texture;
}

vector<float>* Mesh::get_vertices() { return &this->vertices; }

vector<int>* Mesh::get_indices() { return &this->indices; }

int Mesh::get_n_triangles() { return this->n_triangles; }

glm::vec3 Mesh::get_position() { return this->position; }

// TODO: Make this only execute when position or form is changed
vector<float> Mesh::get_positioned_vertices() {
    int offset = 3;  // TODO: Must depend on if using textures or colors
    int stride = (3 + offset);

    vector<float> positioned_vertices;
    positioned_vertices.reserve(3 * stride * this->get_n_triangles());

    for (int i = 0; i < 3 * stride * this->get_n_triangles() / stride; i++) {
        glm::vec4 positioned = glm::vec4((*this->get_vertices())[i * stride] + this->get_position().x,
                                         (*this->get_vertices())[i * stride + 1] + this->get_position().y,
                                         (*this->get_vertices())[i * stride + 2] + this->get_position().z, 1.0f);

        glm::vec3 normalized_projection = glm::vec3(positioned) / positioned.w;
        positioned_vertices.push_back(normalized_projection.x);
        positioned_vertices.push_back(normalized_projection.y);
        positioned_vertices.push_back(normalized_projection.z);

        // Loop with offset amount (all none position elements are ignored)
        for (int j = 0; j < offset; j++) {
            positioned_vertices.push_back((*this->get_vertices())[i * stride + 3 + j]);
        }
    }

    return positioned_vertices;
}

std::optional<Texture> Mesh::get_texture() { return this->texture; }
