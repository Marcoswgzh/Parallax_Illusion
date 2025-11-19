
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "detection/detection.hpp"
#include "gl.h"
#include "render/menu_renderer.hpp"
#include "render/renderer.hpp"
#include "render/scene_renderer.hpp"
#include "scene/projection.hpp"
#include "shaders/shaders.hpp"
#include "window_manager.hpp"
#include "menu/button.hpp"

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

//Globally accessible button
Button menu_button;

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    // TODO: These are very basic move opperations, improve by moving in the
    // look direction
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

 void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            //Convert screen coords to OpenGL NDC coords
            float cx = (xpos/width) * 2.0f - 1.0f;
            float cy = -(ypos/height) * 2.0f + 1.0f;

            if (menu_button.contains(cx, cy)) {
                std::cout << "Reset camera" << std::endl;
                
                //Reset camera position
                camera_x = 0.0f;
                camera_y = 0.5f;
                camera_z = -3.0f;

                //Reset camera view direction
                camera_view_x = 0.0f;
                camera_view_y = 0.0f;
                camera_view_z = 0.0f;
            }
        }
    }

int main() {
    WindowManager* window_manager = WindowManager::get_instance();

    vector<float> scene_pyramid = {
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
    };
    VisualObject object;
    object.triangles = scene_pyramid;
    object.n_triangles = 4;

    Renderer* renderer3D = SceneRenderer::get_instance();
    int piramid_render_index = renderer3D->add(object);

    VisualObject menu_object;
    menu_object.triangles = {
        0.8f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  0.8f, -1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  0.8f, -1.0f, 0.0f, 0.0f, 0.0f,
    };
    menu_object.n_triangles = 4;

    Renderer* renderer2D = MenuRenderer::get_instance();
    renderer2D->add(menu_object);

    std::vector<float> buttonVertices=createButtonVertices(0.82f,0.98f); //createButtonVertices(positionX,positionY)

    VisualObject button_object;
    button_object.triangles=buttonVertices;
    button_object.n_triangles=2;

    menu_button = {
        .x = 0.82f,
        .y = 0.98f,
        .width = 0.16f,
        .height = 0.12f
    }; 

    glfwSetMouseButtonCallback(window_manager->get_window(), mouseButtonCallback);

    renderer2D->add(button_object);

    // Event loop
    while (!glfwWindowShouldClose(window_manager->get_window())) {
        // First handle input
        process_input(window_manager->get_window());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Projector* projector = Projector::get_instance();

        // Project the triangles
        // TODO: This camera refresh should happen in a camera class
        glm::mat4 view = glm::lookAt(glm::vec3(camera_x, camera_y, camera_z),  // Camera position
                                     glm::vec3(camera_view_x, camera_view_y,
                                               camera_view_z),  // Camera view
                                     glm::vec3(0, 1, 0));       // Camera angle
        projector->set_view_projection(view);

        // Draw scene
        renderer3D->draw();

        // Draw menu
        glDisable(GL_DEPTH_TEST);
        renderer2D->draw();
        glEnable(GL_DEPTH_TEST);

        // Swap buffers (refresh the screen with the created render)
        glfwSwapBuffers(window_manager->get_window());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
