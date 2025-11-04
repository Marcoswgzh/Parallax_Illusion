#ifndef PROJECTION
#define PROJECTION

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class Projector {
public:
  Projector(int width, int height);
  void set_view_projection(glm::mat4 view);
  vector<float> project(vector<float> triangles, int n_triangles);

private:
  glm::mat4 projection;
  glm::mat4 view_projection;
};

#endif