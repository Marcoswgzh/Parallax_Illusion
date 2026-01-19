
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>
#include <vector>

#include "delta_time.hpp"
#include "detection/recording.hpp"
#include "gl.h"
#include "mouse.hpp"
#include "render/menu_renderer.hpp"
#include "render/scene_renderer.hpp"
#include "shaders/shaders.hpp"
#include "shapes/apple_cube.hpp"
#include "shapes/cube.hpp"
#include "window_manager.hpp"
#include "menu/menu.hpp"

// Gaze config
// TODO: Shoudn't be configured here, but in camera file
const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

// Temporary "menu" toggle
// TODO: Do this with the menu when it exists
bool menu = true;

void process_input() {
    GLFWwindow* window = WindowManager::get_instance()->get_window();

    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        Recorder* recorder = Recorder::get_instance();
        recorder->toggle();
        std::cout << "Face detection " << (recorder->use_detection() ? "ENABLED" : "DISABLED") << std::endl;
    }

    // Toggle menu (and also if mouse is captured in center for movement)
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        Menu::get_instance()->toggle();
    }
}

int main() {
    // Initialize recorder
    Recorder* recorder = Recorder::get_instance();
    recorder->start();

    // Get instance of window manager
    WindowManager* window_manager = WindowManager::get_instance();

    // Init mouse
    Mouse* mouse = Mouse::get_instance();

    // Create cube for scene
    Cube cube1(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube2(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube3(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 4.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube4(glm::vec3(2.0, 2.0, 2.0), glm::vec3(4.0, 0.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    AppleCube apple_cube(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, -4.0, 0.0));

    // Initiate menu by getting its instance
    Menu::get_instance();

    // Set a key callback for one time keypresses
    glfwSetKeyCallback(window_manager->get_window(), key_callback);

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        DeltaTime::get_instance()->update();
        recorder->update();

        // First handle input
        process_input();

        // Apply gaze input if enabled
        // if (recorder->use_detection()) {
        //     cv::Rect face = recorder->get_face();
        //     cv::Mat frame = recorder->get_frame();
        //     Gaze gaze = camera.compute_gaze_from_facial(face, frame.cols, frame.rows);
        //     camera.update_camera_gaze(gaze, GAZE_SCALE_X, GAZE_SCALE_Y, CAMERA_SMOOTHING);
        // }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw scene
        SceneRenderer::get_instance()->draw();

        // Draw menu
        MenuRenderer::get_instance()->draw();

        // Swap buffers (refresh the screen with the created render)
        glfwSwapBuffers(window_manager->get_window());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
