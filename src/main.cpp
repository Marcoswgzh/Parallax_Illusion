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
#include "shapes/cube.hpp"
#include "window_manager.hpp"
#include "menu/button.hpp"
#include "render/mesh.hpp"

// Gaze config
const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

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

Button menu_button;

// Temporary "menu" toggle
bool menu = true;

void process_input(Camera* camera) {
    GLFWwindow* window = WindowManager::get_instance()->get_window();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->move_forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->move_backward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->move_left();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->move_right();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera->move_up();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera->move_down();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        Recorder* recorder = Recorder::get_instance();
        recorder->toggle();
        std::cout << "Face detection " << (recorder->use_detection() ? "ENABLED" : "DISABLED") << std::endl;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        menu = !menu;
        if (menu) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        float cx = (xpos/width) * 2.0f - 1.0f;
        float cy = -(ypos/height) * 2.0f + 1.0f;

        if (menu_button.contains(cx, cy)) {
            std::cout << "Reset camera" << std::endl;
            camera_x = 0.0f;
            camera_y = 0.5f;
            camera_z = -3.0f;
            camera_view_x = 0.0f;
            camera_view_y = 0.0f;
            camera_view_z = 0.0f;
        }
    }
}

int main() {
    Recorder* recorder = Recorder::get_instance();
    recorder->start();

    WindowManager* window_manager = WindowManager::get_instance();
    Mouse* mouse = Mouse::get_instance();
    Camera camera;
    Cube cube(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.4, 0.8));

    // Menu: hardcoded vertices → Mesh (white panel, 4 triangles)
    std::vector<float> menuVertices = {
        0.8f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.8f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  0.8f, -1.0f, 0.0f, 0.0f, 0.0f
    };
    Mesh menu_mesh(menuVertices, {}, 4, glm::vec3(0.0f));

    Renderer* renderer2D = MenuRenderer::get_instance();
    renderer2D->add(menu_mesh);

    // Button: createButtonVertices(gray) → Mesh (2 triangles)
    std::vector<float> buttonVertices = createButtonVertices(0.82f, 0.98f);
    Mesh button_mesh(buttonVertices, {}, 2, glm::vec3(0.0f));

    // Initialize Button struct for contains() check
    menu_button.x = 0.82f;
    menu_button.y = 0.98f;
    menu_button.width = 0.16f;
    menu_button.height = 0.12f;

    glfwSetMouseButtonCallback(window_manager->get_window(), mouseButtonCallback);
    renderer2D->add(button_mesh);

    glfwSetInputMode(window_manager->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window_manager->get_window(), key_callback);

    while (!glfwWindowShouldClose(window_manager->get_window())) {
        DeltaTime::get_instance()->update();
        recorder->update();

        process_input(&camera);

        if (recorder->use_detection()) {
            cv::Rect face = recorder->get_face();
            cv::Mat frame = recorder->get_frame();
            Gaze gaze = camera.compute_gaze_from_facial(face, frame.cols, frame.rows);
            camera.update_camera_gaze(gaze, GAZE_SCALE_X, GAZE_SCALE_Y, CAMERA_SMOOTHING);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update_mouse_view();
        camera.view();

        SceneRenderer::get_instance()->draw();
        renderer2D->draw();

        glfwSwapBuffers(window_manager->get_window());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
