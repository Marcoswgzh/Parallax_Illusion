#include "mouse.hpp"
#include "window_manager.hpp"
#include "menu/menu.hpp"

Mouse* Mouse::instance = nullptr;
static bool first = true;

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
    Mouse* mouse = Mouse::get_instance();
    if (first) {
        mouse->previous_x = x_pos;
        mouse->previous_y = y_pos;
        first = false;
    }

    // Recalculate the deltas
    mouse->x_delta = x_pos - mouse->previous_x;
    mouse->y_delta = y_pos - mouse->previous_y;

    // Adjust the previous mouse coordinates
    mouse->previous_x = x_pos;
    mouse->previous_y = y_pos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS){
        return;
    }

    double x_position, y_position;
    glfwGetCursorPos(window, &x_position, &y_position);
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    Mouse* mouse = Mouse::get_instance();
    glm::vec2 click_position((x_position / width) * 2.0f - 1.0f, -(y_position / height) * 2.0f + 1.0f);
    Menu::get_instance()->handle_click_events(click_position);
}

Mouse* Mouse::get_instance() {
    if (instance == nullptr) {
        instance = new Mouse();
    }

    return instance;
}

Mouse::Mouse() {
    WindowManager* window_manager = WindowManager::get_instance();
    glfwSetCursorPosCallback(window_manager->get_window(), mouse_callback);
    glfwSetMouseButtonCallback(window_manager->get_window(), mouseButtonCallback);
}
