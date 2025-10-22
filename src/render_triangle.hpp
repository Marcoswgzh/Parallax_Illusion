#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <glad.h>

class TriangleRenderer {
public:
  TriangleRenderer(float triangles[], int n_traingles);
  void draw();

private:
  int n_traingles;
  unsigned int VAO;
};

#endif