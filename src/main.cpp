#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "camera/camera.hpp"
#include "delta_time.hpp"
#include "detection/recording.hpp"
#include "gl.h"
#include "mouse.hpp"
#include "render/menu_renderer.hpp"
#include "render/renderer.hpp"
#include "render/scene_renderer.hpp"
#include "shaders/shaders.hpp"
#include "window_manager.hpp"

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
        menu = !menu;
        if (menu) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void global_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Mouse::get_instance()->mouse_callback(window, xpos, ypos);
}

int main() {
    // Initialize recorder
    Recorder* recorder = Recorder::get_instance();
    recorder->start();

    // Get instance of window manager
    WindowManager* window_manager = WindowManager::get_instance();

    // Init mouse
    Mouse* mouse = Mouse::get_instance();

    // Initialize camera
    Camera camera;

    vector<float> scene_pyramid = {
        0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        0.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,

        1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

        0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
    };
    vector<int> scene_pyramid_indices = {0, 1, 2, 0, 3, 4, 0, 4, 5, 0, 5, 1};
    Mesh pyramid_mesh(scene_pyramid, scene_pyramid_indices, 4);

    Renderer* renderer3D = SceneRenderer::get_instance();
    int piramid_render_index = renderer3D->add(pyramid_mesh);

    vector<float> triangles = {
        0.8f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.8f, -1.0f, 1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.8f, -1.0f, 1.0f, 0.0f, 0.0f,
    };
    Mesh menu_mesh(triangles, {}, 4);

    Renderer* renderer2D = MenuRenderer::get_instance();
    renderer2D->add(menu_mesh);

    // Captures the mouse, so it can be used for movement
    glfwSetInputMode(window_manager->get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Set a key callback for one time keypresses
    glfwSetKeyCallback(window_manager->get_window(), key_callback);

    glfwSetCursorPosCallback(window_manager->get_window(), global_mouse_callback);

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        DeltaTime::get_instance()->update();
        recorder->update();

        // First handle input
        process_input();

        camera.update();

        // Apply gaze input if enabled
        if (recorder->use_detection()) {
            cv::Rect face = recorder->get_face();
            if (face.width > 0) {
                cv::Mat frame = recorder->get_frame();
                Gaze gaze = camera.compute_gaze_from_face(face, frame.cols, frame.rows);
                camera.update_position_from_face(gaze, (float)face.width);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculates a view matrix to look at the scene
        camera.view();

        // Draw scene
        renderer3D->draw();

        // Draw menu
        renderer2D->draw();

        // Swap buffers (refresh the screen with the created render)
        glfwSwapBuffers(window_manager->get_window());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
