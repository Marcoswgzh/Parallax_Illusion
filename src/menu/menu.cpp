#include <iostream>

#include "menu.hpp"
#include "../mouse.hpp"
#include "../window_manager.hpp"
#include "../render/scene_renderer.hpp"
#include "../scenes/scene_handler.hpp"

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

    if (this->scene_1_button.contains(position) && this->scene_1_button.should_display()) {
        SceneRenderer::get_instance()->remove_current_scene();
        SceneHandler::get_instance()->show_scene_1();
        this->toggle();
    }

    if (this->scene_2_button.contains(position) && this->scene_2_button.should_display()) {
        SceneRenderer::get_instance()->remove_current_scene();
        SceneHandler::get_instance()->show_scene_2();
        this->toggle();
    }

    if (this->scene_3_button.contains(position) && this->scene_3_button.should_display()) {
        SceneRenderer::get_instance()->remove_current_scene();
        SceneHandler::get_instance()->show_scene_3();
        this->toggle();
    }
}

void Menu::toggle() {
    this->display = !this->display;
    this->container.toggle_display();
    this->menu_title.toggle_display();
    this->scene_1_button.toggle_display();
    this->scene_2_button.toggle_display();
    this->scene_3_button.toggle_display();

    if (!this->display) {
        glfwSetInputMode(WindowManager::get_instance()->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(WindowManager::get_instance()->get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // Also toggle any camera movement
    SceneRenderer::get_instance()->toggle_movement();
}

bool Menu::should_display() {
    return this->display;
}
