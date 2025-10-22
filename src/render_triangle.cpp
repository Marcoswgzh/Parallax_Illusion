#include "render_triangle.hpp"
#include <cstddef>
#include <glad.h>
#include <iostream>
using namespace std;

TriangleRenderer::TriangleRenderer(float triangles[], int n_traingles) {
  this->n_traingles = n_traingles;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // TODO: Make GL_STATIC_DRAW an option (some flag movable)
  // TODO: Don't use 18 * sizeof(float)
  glBufferData(GL_ARRAY_BUFFER, n_traingles * 18 * sizeof(float), triangles,
               GL_STATIC_DRAW);

  // Tell OpenGL how it should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VAO
  glBindVertexArray(0);
}

void TriangleRenderer::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, n_traingles * 6);
}