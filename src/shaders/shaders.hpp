#ifndef SHADER
#define SHADER

#include <glad.h>
#include <string>
using namespace std;

class Shader {
public:
  Shader();
  void use();

private:
  const char *vertex_shader_source;
  const char *fragmentation_shader_source;
  unsigned int shaderId;

  string readShader(const char *path);
  unsigned int load(string haderSource, GLenum shaderType);
};

#endif