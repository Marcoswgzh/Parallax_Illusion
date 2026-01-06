
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "camera/camera.hpp"
#include "detection/recording.hpp"
#include "gl.h"
#include "render/menu_renderer.hpp"
#include "render/renderer.hpp"
#include "render/scene_renderer.hpp"
#include "scene/projection.hpp"
#include "shaders/shaders.hpp"
#include "window_manager.hpp"

// Gaze config
const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

void process_input(GLFWwindow* window, Camera* camera, Recorder* recorder) {
    // WASD + vertical
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->move(0.0f, 0.0f, camera->get_speed());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->move(0.0f, 0.0f, -camera->get_speed());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->move(camera->get_speed(), 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->move(-camera->get_speed(), 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera->move(0.0f, camera->get_speed(), 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera->move(0.0f, -camera->get_speed(), 0.0f);

    // Toggle detection
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        recorder->toggle();
        std::cout << "Face detection " << (recorder->use_detection() ? "ENABLED" : "DISABLED") << std::endl;
    }

    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialize recorder
    Recorder recorder;
    recorder.start();

    // Initialize camera
    Camera camera;

    WindowManager* window_manager = WindowManager::get_instance();

    vector<float> scene_pyramid = {
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
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

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        recorder.update();

        // First handle input
        process_input(window_manager->get_window(), &camera, &recorder);

        // Apply gaze input if enabled
        if (recorder.use_detection()) {
            cv::Rect face = recorder.get_face();
            cv::Mat frame = recorder.get_frame();
            Gaze gaze = camera.compute_gaze_from_facial(face, frame.cols, frame.rows);
            camera.update_camera_gaze(gaze, GAZE_SCALE_X, GAZE_SCALE_Y, CAMERA_SMOOTHING);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Compute view matrix
        glm::vec3 cam_pos = camera.get_camera_position();
        glm::vec3 cam_target = camera.get_camera_target();
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
