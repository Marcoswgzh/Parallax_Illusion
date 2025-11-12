#include "window_manager.hpp"

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

WindowManager::WindowManager() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // only for apple?

    // TODO: Create a window manager
    // Initial width and height
    int width = 800;
    int height = 600;
    this->window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    // Set a callback function for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Enable depth testing (closer objects are drawn over further objects)
    glEnable(GL_DEPTH_TEST);

    // Set a background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

GLFWwindow* WindowManager::get_window() { return this->window; }