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
#include "camera/camera.hpp"

// Initial screen size
int width = 800;
int height = 600;

// Movement speed
float camera_speed = 0.02;

// Gaze config
const float GAZE_SCALE_X = 1.2f;
const float GAZE_SCALE_Y = 0.8f;
const float CAMERA_SMOOTHING = 0.18f;

// Detection toggle
bool use_detection = true;

// ---------- GLFW input ----------
void framebuffer_size_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void process_input(GLFWwindow *window)
{
    // WASD + vertical
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        update_camera_input(0.f, 0.f, camera_speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        update_camera_input(0.f, 0.f, -camera_speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        update_camera_input(camera_speed, 0.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        update_camera_input(-camera_speed, 0.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        update_camera_input(0.f, camera_speed, 0.f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        update_camera_input(0.f, -camera_speed, 0.f);

    // Toggle detection
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

    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    };
    int n_triangles = 4;
    TriangleRenderer renderer;
    int pyramid_render_index = renderer.add(triangles, n_triangles);

    int fb_w, fb_h;
    glfwGetFramebufferSize(window, &fb_w, &fb_h);
    Projector projector(fb_w, fb_h);
    cv::Mat frame;

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        cap >> frame;

        // Apply gaze input if enabled
        if (use_detection && !frame.empty())
        {
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
        projector.set_view_projection(view);

        // Project triangles
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
