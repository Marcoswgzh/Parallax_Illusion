#include "gl.h"
#include "render/scene_renderer.hpp"
#include "menu/menu.hpp"
#include "detection/recording.hpp"
#include "window_manager.hpp"
#include "mouse.hpp"
#include "render/menu_renderer.hpp"
#include "delta_time.hpp"

void process_input() {
    GLFWwindow* window = WindowManager::get_instance()->get_window();

    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Toggle menu (and also if mouse is captured in center for movement)
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        Menu::get_instance()->toggle();
    }

    // Toggle key-based movement
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        SceneRenderer::get_instance()->toggle_key_movement();
    }

    // Switch between light types
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        SceneRenderer::get_instance()->set_light_type(LightType::Ambient);
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        SceneRenderer::get_instance()->set_light_type(LightType::Diffusion);
    }

    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        SceneRenderer::get_instance()->set_light_type(LightType::Phong);
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

    // Initiate menu by getting its instance
    Menu::get_instance();

    // Set a key callback for one time keypresses
    glfwSetKeyCallback(window_manager->get_window(), key_callback);

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        // Update the delta time
        DeltaTime::get_instance()->update();

        // First handle input
        process_input();

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
