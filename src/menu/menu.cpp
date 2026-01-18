#include "menu.hpp"
#include "container.hpp"

#include <optional>

Menu::Menu() {
    // Create menu container
    Container container(std::nullopt, glm::vec2(0.0), glm::vec2(0.5), glm::vec3(1.0));

    Button button(container, glm::vec2(0.0, 0.0), glm::vec2(0.1), glm::vec3(0.0));
}