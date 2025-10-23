// ORDER MATTERS: glad.h must be included before any GLFW or OpenGL libraries.
#include <glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "detection/detection.hpp"
#include "render/render_triangle.hpp"
#include "shaders/shaders.hpp"
#include "view/projection.hpp"

// Initial screen size (not constant)
int width = 800;
int height = 600;

// Camera position
float camera_x = 0;
float camera_y = 0.5;
float camera_z = -3;
float camera_speed = 0.02;

// Camera look at
float camera_view_x = 0;
float camera_view_y = 0;
float camera_view_z = 0;
float camera_angle_delta = 1;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // TODO: These are very basic move opperations, improve by moving in the look
  // direction
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera_z += camera_speed;
    camera_view_z += camera_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera_z -= camera_speed;
    camera_view_z -= camera_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera_x += camera_speed;
    camera_view_x += camera_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera_x -= camera_speed;
    camera_view_x -= camera_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    camera_y -= camera_speed;
    camera_view_y -= camera_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    camera_y += camera_speed;
    camera_view_y += camera_speed;
  }

  // Control camera perspective with keys
  // TODO:
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
  }

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
  }

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
  }
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

  // Enable depth testing (closer objects are drawn over further objects)
  glEnable(GL_DEPTH_TEST);

  // Set a background color
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Initialize shaders and set them as the currently used
  Shader shaders;
  shaders.use();

  vector<float> triangles = {
      0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
      0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f,  1.0f, 0.0f,
  };
  int n_triangles = 4;
  TriangleRenderer renderer;
  int piramid_render_index = renderer.add(triangles, n_triangles);

  // Use the width and height from the viewport
  int projector_width, projector_height;
  glfwGetFramebufferSize(window, &projector_width, &projector_height);
  Projector projector(projector_width, projector_height);

  // Event loop
  while (!glfwWindowShouldClose(window)) {
    // First handle input
    process_input(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Project the triangles
    glm::mat4 view = glm::lookAt(
        glm::vec3(camera_x, camera_y, camera_z), // Camera position
        glm::vec3(camera_view_x, camera_view_y, camera_view_z), // Camera view
        glm::vec3(0, 1, 0));                                    // Camera angle
    projector.set_view_projection(view);

    vector<float> projected_triangles;
    projected_triangles.reserve(18 * n_triangles);
    for (int i = 0; i < 18 * n_triangles / 6; i++) {
      glm::vec4 projected = projector.get_view_projection() *
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

    renderer.replace(0, projected_triangles, n_triangles, n_triangles);
    renderer.draw();

    // Swap buffers (refresh the screen with the created render)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // detect_and_show();
  glfwTerminate();
  return 0;
}
