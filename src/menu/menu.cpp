#include <iostream>

#include "menu.hpp"
#include "../mouse.hpp"

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

    if (this->scene_1.contains(position)) {
        std::cout << "Scene 1" << std::endl;
    }

    if (this->scene_2.contains(position)) {
        std::cout << "Scene 2" << std::endl;
    }

    if (this->scene_3.contains(position)) {
        std::cout << "Scene 3" << std::endl;
    }
}