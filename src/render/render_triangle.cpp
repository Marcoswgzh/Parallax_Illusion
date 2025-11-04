#include "render_triangle.hpp"
#include <cstddef>
#include <glad.h>
#include <iostream>
using namespace std;

TriangleRenderer *TriangleRenderer::instance = nullptr;

TriangleRenderer::TriangleRenderer() {}

TriangleRenderer *TriangleRenderer::get_instance() {
  if (instance == nullptr) {
    instance = new TriangleRenderer();
  }
  return instance;
}

void TriangleRenderer::update() {
  vector<float> flattened = this->get_flattened();

  // TODO: Currently fails if multiple instances of triangle renderer are
  // made (not sure)?
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // TODO: Make GL_STATIC_DRAW an option (some flag movable)
  glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 18 * sizeof(float),
               flattened.data(), GL_STATIC_DRAW);

  // Tell OpenGL how it should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VBO and VAO
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

vector<float> TriangleRenderer::get_flattened() {
  // First flatten the triangle data
  vector<float> flattened;
  flattened.reserve(this->n_triangles * 18);

  for (VisualObject object : this->visual_objects) {
    flattened.insert(flattened.end(), object.triangles.begin(),
                     object.triangles.end());
  }

  return flattened;
}

int TriangleRenderer::add(VisualObject object) {
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

void TriangleRenderer::replace(int index, vector<float> triangles,
                               int n_triangles, int n_previous_triangles) {
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

void TriangleRenderer::remove(int index, int n_triangles) {
  // Make sure the change is noted
  this->change = true;

  // Update the total amount of triangles and number of visual objects
  this->n_triangles -= n_triangles;
  this->n_visual_objects -= 1;

  // Remove the visual object
  // TODO: Make sure this indexing is correct
  this->visual_objects.erase(this->visual_objects.begin() + index);
}

void TriangleRenderer::draw() {
  // Don't execute if there is nothing to draw
  if (this->n_triangles <= 0) {
    return;
  }

  // If there was a change, update
  if (this->change) {
    this->update();
  }

  glBindVertexArray(VAO);

  // TODO: Make sure last argument is correct
  glDrawArrays(GL_TRIANGLES, 0, n_triangles * 3);

  this->change = false;
}