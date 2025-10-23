// ORDER MATTERS: glad.h must be included before any GLFW or OpenGL libraries.
#include <glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "detection/detection.hpp"
#include "projection.hpp"
#include "render_triangle.hpp"
#include "shaders.hpp"

// Initial screen size (not constant)
int width = 800;
int height = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // only for apple?

  GLFWwindow *window =
      glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set a callback function for window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize shaders and set them as the currently used
  Shader shaders;
  shaders.use();

  float triangles[] = {
      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
      0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
  };
  int n_triangles = 4;
  TriangleRenderer renderer;

  // Use the width and height from the viewport
  int projector_width, projector_height;
  glfwGetFramebufferSize(window, &projector_width, &projector_height);
  Projector projector(projector_width, projector_height);

  // Event loop
  while (!glfwWindowShouldClose(window)) {
    // First handle input
    process_input(window);

    // Handle rendering here
    // Set a background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Project the triangles
    glm::mat4 view = glm::lookAt(glm::vec3(1.0, 0.5, -3.0), glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    projector.set_view_projection(view);

    float projected_triangles[18 * n_triangles];
    for (int i = 0; i < 18 * n_triangles / 6; i++) {
      glm::vec4 projected = projector.get_view_projection() *
                            glm::vec4(triangles[i * 6], triangles[i * 6 + 1],
                                      triangles[i * 6 + 2], 1.0f);

      glm::vec3 normalized_projection = glm::vec3(projected) / projected.w;
      projected_triangles[i * 6] = normalized_projection.x;
      projected_triangles[i * 6 + 1] = normalized_projection.y;
      projected_triangles[i * 6 + 2] = normalized_projection.z;
      projected_triangles[i * 6 + 3] = triangles[i * 6 + 3];
      projected_triangles[i * 6 + 4] = triangles[i * 6 + 4];
      projected_triangles[i * 6 + 5] = triangles[i * 6 + 5];
    }

    renderer.update(projected_triangles, n_triangles);
    renderer.draw();

    // Swap buffers (refresh the screen with the created render)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // detect_and_show();
  glfwTerminate();
  return 0;
}
