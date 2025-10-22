#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <glad.h>

class TriangleRenderer {
public:
  TriangleRenderer(float vertices[]);
  void draw();

private:
  unsigned int VAO;
  unsigned int shaderProgram;

  unsigned int load_shader(char const *shaderSource, GLenum shaderType);
  void setup_shaders();
};

#endif