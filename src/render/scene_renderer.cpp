#include "scene_renderer.hpp"
#include "renderer.hpp"
#include <iostream>
using namespace std;

SceneRenderer *SceneRenderer::instance = nullptr;

SceneRenderer *SceneRenderer::get_instance() {
  if (instance == nullptr) {
    instance = new SceneRenderer();
  }
  return instance;
}

SceneRenderer::SceneRenderer() {}

void SceneRenderer::update() {
  vector<float> flattened = this->get_flattened();

  glGenVertexArrays(RenderGroups::Scene, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(RenderGroups::Scene, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, this->n_triangles * 18 * sizeof(float),
               flattened.data(), GL_DYNAMIC_DRAW);

  // Tell OpenGL how it should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  this->change = false;
}

vector<float> SceneRenderer::get_flattened() {
  // First flatten the triangle data
  vector<float> flattened;
  flattened.reserve(this->n_triangles * 18);

  for (VisualObject object : this->visual_objects) {
    flattened.insert(flattened.end(), object.triangles.begin(),
                     object.triangles.end());
  }

  return flattened;
}

void SceneRenderer::draw() {
  // Don't execute if there is nothing to draw
  if (this->n_triangles <= 0) {
    return;
  }

  // If there was a change, update
  if (this->change) {
    this->update();
  }

  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, this->n_triangles * 3);
}