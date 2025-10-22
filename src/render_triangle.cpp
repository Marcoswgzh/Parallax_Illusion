#include "render_triangle.hpp"
#include <cstddef>
#include <glad.h>
#include <iostream>

char const *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

char const *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// TODO: Change input to a sequence of triangles
TriangleRenderer::TriangleRenderer(float vertices[]) {
  setup_shaders();

  unsigned int VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // TODO: Make GL_STATIC_DRAW an option (some flag movable)
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

  // Tell OpenGL how it should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); // Unbind VAO
}

void TriangleRenderer::setup_shaders() {
  unsigned int vertexShader = load_shader(vertexShaderSource, GL_VERTEX_SHADER);
  unsigned int fragmentShader =
      load_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check if linking the shader program was succesful
  int success;
  int logLength = 512;
  char infoLog[logLength];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR: Linking shader program failed: \n"
              << infoLog << std::endl;
  }

  // Delete the shader objects, because we don't need them anymore (already
  // linked)
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

unsigned int TriangleRenderer::load_shader(char const *shaderSource,
                                           GLenum shaderType) {
  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  // Check if the shader compilation was succesful
  int success;
  int logLength = 512;
  char infoLog[logLength];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, logLength, NULL, infoLog);
    std::cout << "ERROR: Shader compilation failed: \n" << infoLog << std::endl;
  }

  return shader;
}

void TriangleRenderer::draw() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}