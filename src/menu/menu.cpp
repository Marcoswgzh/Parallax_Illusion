#include <iostream>

#include "menu.hpp"
#include "../mouse.hpp"
#include "../window_manager.hpp"

Menu* Menu::instance = nullptr;

Menu* Menu::get_instance() {
    if (instance == nullptr) {
        instance = new Menu();
    }
    return instance;
}

Menu::Menu() {}

void Menu::handle_click_events(glm::vec2 position) {
    Mouse* mouse = Mouse::get_instance();

    if (this->scene_1.contains(position) && this->scene_1.should_display()) {
        std::cout << "Scene 1" << std::endl;
    }

    if (this->scene_2.contains(position) && this->scene_2.should_display()) {
        std::cout << "Scene 2" << std::endl;
    }

    if (this->scene_3.contains(position) && this->scene_3.should_display()) {
        std::cout << "Scene 3" << std::endl;
    }
}

void Menu::toggle() {
    this->display = !this->display;
    this->container.toggle_display();
    this->scene_1.toggle_display();
    this->scene_2.toggle_display();
    this->scene_3.toggle_display();

    if (!this->display) {
        glfwSetInputMode(WindowManager::get_instance()->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(WindowManager::get_instance()->get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

bool Menu::should_display() {
    return this->display;
}