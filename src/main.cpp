
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "camera/camera.hpp"
#include "detection/detection.hpp"
#include "gl.h"
#include "render/menu_renderer.hpp"
#include "render/renderer.hpp"
#include "render/scene_renderer.hpp"
#include "scene/projection.hpp"
#include "shaders/shaders.hpp"
#include "window_manager.hpp"

// Movement speed
float camera_speed = 0.02;

// Detection toggle
bool use_detection = true;

// Gaze config
const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

void process_input(GLFWwindow* window) {
    // WASD + vertical
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) update_camera_input(0.f, 0.f, camera_speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) update_camera_input(0.f, 0.f, -camera_speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) update_camera_input(camera_speed, 0.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) update_camera_input(-camera_speed, 0.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) update_camera_input(0.f, camera_speed, 0.f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) update_camera_input(0.f, -camera_speed, 0.f);

    // Toggle detection
    static bool togglePressedBefore = false;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        if (!togglePressedBefore) {
            use_detection = !use_detection;
            std::cout << "Face detection " << (use_detection ? "ENABLED" : "DISABLED") << std::endl;
        }
        togglePressedBefore = true;
    } else
        togglePressedBefore = false;

    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    // Start detection
    if (!detect_and_show()) return -1;

    WindowManager* window_manager = WindowManager::get_instance();

    vector<float> scene_pyramid = {
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    };
    vector<int> scene_pyramid_indices = {0, 1, 2, 0, 3, 4, 0, 4, 5, 0, 5, 1};
    VisualObject object;
    object.triangles = scene_pyramid;
    object.indices = scene_pyramid_indices;
    object.n_triangles = 4;

    Renderer* renderer3D = SceneRenderer::get_instance();
    int piramid_render_index = renderer3D->add(object);

    VisualObject menu_object;
    menu_object.triangles = {
        0.8f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.8f, -1.0f, 1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.8f, -1.0f, 1.0f, 0.0f, 0.0f,
    };
    menu_object.n_triangles = 4;

    Renderer* renderer2D = MenuRenderer::get_instance();
    renderer2D->add(menu_object);

    cv::Mat frame;

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        // First handle input
        process_input(window_manager->get_window());

        cap >> frame;

        // Apply gaze input if enabled
        if (use_detection && !frame.empty()) {
            Gaze g = compute_gaze_from_frame(frame);
            if (g.valid)
                update_camera_gaze(g, GAZE_SCALE_X, GAZE_SCALE_Y, CAMERA_SMOOTHING);
            else
                reset_camera_gaze(CAMERA_SMOOTHING);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Compute view matrix
        glm::vec3 cam_pos = get_camera_position();
        glm::vec3 cam_target = get_camera_target();
        glm::mat4 view = glm::lookAt(cam_pos, cam_target, glm::vec3(0, 1, 0));

        Projector* projector = Projector::get_instance();
        projector->set_view_projection(view);

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
