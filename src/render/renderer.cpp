#include "renderer.hpp"

#include <cstddef>
#include <iostream>

#include "scene_renderer.hpp"
using namespace std;

int Renderer::add(Mesh mesh) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles and number of visual objects
    this->n_triangles += mesh.get_n_triangles();

    // Add the triangles from the current object to the triangles vector
    this->meshes.push_back(mesh);

    // Return the index of the added item (for later control of the visual
    // object)
    return this->meshes.size();
}

void Renderer::replace(int index, vector<float> triangles, int n_triangles, int n_previous_triangles) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles
    this->n_triangles -= n_previous_triangles;
    this->n_triangles += n_triangles;

    // Create the new mesh
    Mesh mesh(triangles, {}, n_triangles);

    // Replace the visual object
    this->meshes[index] = mesh;
}

void Renderer::remove(int index, int n_triangles) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles and number of visual objects
    this->n_triangles -= n_triangles;

    // Remove the visual object
    // TODO: Make sure this indexing is correct
    this->meshes.erase(this->meshes.begin() + index);
}