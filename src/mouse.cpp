#include "mouse.hpp"

#include "window_manager.hpp"

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

Mouse* Mouse::get_instance() {
    if (instance == nullptr) {
        instance = new Mouse();
    }
    return instance;
}

Mouse::Mouse() {
    WindowManager* window_manager = WindowManager::get_instance();
    glfwSetCursorPosCallback(window_manager->get_window(), mouse_callback);
}