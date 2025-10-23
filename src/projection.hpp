#ifndef PROJECTION
#define PROJECTION

#include <glm/glm.hpp>

class Projector {
public:
  Projector(int width, int height);
  void set_view_projection(glm::mat4 view);
  glm::mat4 get_view_projection();

private:
  glm::mat4 projection;
  glm::mat4 view_projection;
};

#endif