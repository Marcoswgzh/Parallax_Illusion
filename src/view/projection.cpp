#include "projection.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using namespace std;

/**
 * Sets the projectors perspective 'settings'.
 */
Projector::Projector(int width, int height) {
  float fov = glm::radians(45.0f);
  projection = glm::perspective(glm::radians(45.0f),
                                (float)width / (float)height, 0.1f, 100.0f);
}

void Projector::set_view_projection(glm::mat4 view) {
  view_projection = projection * view;
}

vector<float> Projector::project(vector<float> triangles, int n_triangles) {
  vector<float> projected_triangles;
  projected_triangles.reserve(18 * n_triangles);
  for (int i = 0; i < 18 * n_triangles / 6; i++) {
    glm::vec4 projected = this->view_projection *
                          glm::vec4(triangles[i * 6], triangles[i * 6 + 1],
                                    triangles[i * 6 + 2], 1.0f);

    glm::vec3 normalized_projection = glm::vec3(projected) / projected.w;
    projected_triangles.push_back(normalized_projection.x);
    projected_triangles.push_back(normalized_projection.y);
    projected_triangles.push_back(normalized_projection.z);
    projected_triangles.push_back(triangles[i * 6 + 3]);
    projected_triangles.push_back(triangles[i * 6 + 4]);
    projected_triangles.push_back(triangles[i * 6 + 5]);
  }

  return projected_triangles;
}
