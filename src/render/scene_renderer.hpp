#ifndef SCENE_RENDERER
#define SCENE_RENDERER

#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <glad.h>
#include <vector>
using namespace std;

class SceneRenderer : public Renderer {
public:
  static SceneRenderer *get_instance(GLFWwindow *window);

  // Scene renderer should not be cloneable
  SceneRenderer(SceneRenderer &other) = delete;

  // Scene renderer should not be assignable
  void operator=(const SceneRenderer &) = delete;

  void draw() override;

private:
  SceneRenderer(GLFWwindow *window);
  vector<float> get_flattened() override;
  void update() override;

  static SceneRenderer *instance;

  // TODO: Temporary window pointer
  GLFWwindow *window;
};

#endif