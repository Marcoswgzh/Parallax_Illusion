#include "renderer.hpp"

#include <cstddef>
#include <iostream>

#include "scene_renderer.hpp"
using namespace std;

int Renderer::add(VisualObject object) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles and number of visual objects
    this->n_triangles += object.n_triangles;
    this->n_visual_objects += 1;

    // Add the triangles from the current object to the triangles vector
    this->visual_objects.push_back(object);

    // Return the index of the added item (for later control of the visual
    // object)
    return this->n_visual_objects - 1;
}

void Renderer::replace(int index, vector<float> triangles, int n_triangles, int n_previous_triangles) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles
    this->n_triangles -= n_previous_triangles;
    this->n_triangles += n_triangles;

    // Create the visual object
    VisualObject visual_object;
    visual_object.triangles = triangles;
    visual_object.n_triangles = n_triangles;

    // Replace the visual object
    this->visual_objects[index] = visual_object;
}

void Renderer::remove(int index, int n_triangles) {
    // Make sure the change is noted
    this->change = true;

    // Update the total amount of triangles and number of visual objects
    this->n_triangles -= n_triangles;
    this->n_visual_objects -= 1;

    // Remove the visual object
    // TODO: Make sure this indexing is correct
    this->visual_objects.erase(this->visual_objects.begin() + index);
}