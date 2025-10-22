#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <glad.h>

class TriangleRenderer {
public:
  TriangleRenderer(float vertices[]);
  void draw();

private:
  unsigned int VAO;
};

#endif