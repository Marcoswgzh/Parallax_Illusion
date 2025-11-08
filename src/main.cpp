#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <opencv2/opencv.hpp>

#include "detection/detection.hpp"
#include "render/render_triangle.hpp"
#include "shaders/shaders.hpp"
#include "view/projection.hpp"
#include "gaze/gaze.hpp"

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

const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

// Parallax configuration
const float PARALLAX_SCALE_X = 0.3f;
const float PARALLAX_SCALE_Y = 0.2f;
const float PARALLAX_SMOOTHING = 0.05f;

bool use_detection = true;

float interpolate(float a, float b, float t) { return a + (b - a) * t; }

// ---------- GLFW input ----------
void framebuffer_size_callback(GLFWwindow *window, int w, int h)
{
  glViewport(0, 0, w, h);
}

void process_input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    camera_z += camera_speed;
    camera_view_z += camera_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    camera_z -= camera_speed;
    camera_view_z -= camera_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    camera_x += camera_speed;
    camera_view_x += camera_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    camera_x -= camera_speed;
    camera_view_x -= camera_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    camera_y += camera_speed;
    camera_view_y += camera_speed;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    camera_y -= camera_speed;
    camera_view_y -= camera_speed;
  }

  static bool togglePressedBefore = false;
  if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
  {
    if (!togglePressedBefore)
    {
      use_detection = !use_detection;
      std::cout << "Face detection " << (use_detection ? "ENABLED" : "DISABLED") << std::endl;
    }
    togglePressedBefore = true;
  }
  else
    togglePressedBefore = false;
}

// ---------- Main ----------
int main()
{
  if (!detect_and_show())
    return -1;

  if (!glfwInit())
  {
    std::cerr << "GLFW init failed\n";
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(width, height, "OpenCV+OpenGL", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed create window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "GLAD init failed\n";
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2f, 0.3f, 0.3f, 1.f);

  Shader shaders;
  shaders.use();

  // Triangle data
  std::vector<float> triangles = {
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
  int pyramid_render_index = renderer.add(triangles, n_triangles);

  int fb_w, fb_h;
  glfwGetFramebufferSize(window, &fb_w, &fb_h);
  Projector projector(fb_w, fb_h);
  cv::Mat frame;
  Gaze last_gaze{0.f, 0.f, false};

  // Base camera position
  float base_camera_x = 0.f;
  float base_camera_y = 0.5f;
  float base_camera_z = -3.f;

  while (!glfwWindowShouldClose(window))
  {
    process_input(window);

    cap >> frame;

    // ---------- Compute parallax camera view ----------
    if (use_detection && !frame.empty())
    {
      Gaze g = compute_gaze_from_frame(frame);
      if (g.valid)
      {
        last_gaze = g;

        float target_view_x = g.x * GAZE_SCALE_X;
        float target_view_y = g.y * GAZE_SCALE_Y;
        float target_view_z = 0.f;

        camera_view_x = interpolate(camera_view_x, target_view_x, CAMERA_SMOOTHING);
        camera_view_y = interpolate(camera_view_y, target_view_y, CAMERA_SMOOTHING);
        camera_view_z = interpolate(camera_view_z, target_view_z, CAMERA_SMOOTHING);
      }
      else
      {
        // Slowly return view to center
        camera_view_x = interpolate(camera_view_x, 0.f, 0.01f);
        camera_view_y = interpolate(camera_view_y, 0.f, 0.01f);
        camera_view_z = interpolate(camera_view_z, 0.f, 0.01f);
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ---------- Camera/view ----------
    glm::vec3 cam_pos(base_camera_x, base_camera_y, base_camera_z);
    glm::vec3 cam_target = cam_pos + glm::vec3(camera_view_x, camera_view_y, 1.f); // look forward + parallax offsets
    glm::mat4 view = glm::lookAt(cam_pos, cam_target, glm::vec3(0, 1, 0));
    projector.set_view_projection(view);

    // ---------- Project triangles ----------
    std::vector<float> projected;
    projected.reserve(18 * n_triangles);
    for (int i = 0; i < 18 * n_triangles / 6; i++)
    {
      glm::vec4 p = projector.get_view_projection() *
                    glm::vec4(triangles[i * 6], triangles[i * 6 + 1], triangles[i * 6 + 2], 1.f);
      glm::vec3 np = glm::vec3(p) / p.w;
      projected.push_back(np.x);
      projected.push_back(np.y);
      projected.push_back(np.z);
      projected.push_back(triangles[i * 6 + 3]);
      projected.push_back(triangles[i * 6 + 4]);
      projected.push_back(triangles[i * 6 + 5]);
    }
    renderer.replace(pyramid_render_index, projected, n_triangles, n_triangles);
    renderer.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  cap.release();
  cv::destroyAllWindows();
  glfwTerminate();
  return 0;
}
