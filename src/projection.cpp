#include "projection.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Projector::Projector(int width, int height) {
  float fov = glm::radians(45.0f);
  projection = glm::perspective(glm::radians(45.0f),
                                (float)width / (float)height, 0.1f, 100.0f);
}

void Projector::set_view_projection(glm::mat4 view) {
  view_projection = projection * view;
}

glm::mat4 Projector::get_view_projection() { return view_projection; }