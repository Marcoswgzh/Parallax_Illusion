#include <iostream>

#include "frame.hpp"
#include "../render/menu_renderer.hpp"

Frame::Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color, int z_level) {
    MenuRenderer* menu_renderer = MenuRenderer::get_instance();

    // Calculate vertices for menu
    vector<float> vertices = {
        // Triangle 1
        position.x, position.y, color.x, color.y, color.z,

        position.x + size.x, position.y, color.x, color.y, color.z,

        position.x, position.y + size.y, color.x, color.y, color.z,


        // Triangle 2
        position.x + size.x, position.y + size.y, color.x, color.y, color.z,

        position.x, position.y + size.y, color.x, color.y, color.z,

        position.x + size.x, position.y, color.x, color.y, color.z,
    };

    // Store frame info
    this->position = position;
    this->size = size;
    this->z_level = z_level;
    this->id = menu_renderer->add(Surface(vertices, 2, glm::vec2(0.0), this->z_level));
}

Frame::Frame(glm::vec2 position, glm::vec2 size, Texture texture, int z_level) {
    MenuRenderer* menu_renderer = MenuRenderer::get_instance();

    // Calculate vertices for menu
    vector<float> vertices = {
        // Triangle 1
        position.x, position.y, 0.0, 1.0,

        position.x + size.x, position.y, 1.0, 1.0,

        position.x, position.y + size.y, 0.0, 0.0,


        // Triangle 2
        position.x + size.x, position.y + size.y, 1.0, 0.0,

        position.x, position.y + size.y, 0.0, 0.0,

        position.x + size.x, position.y, 1.0, 1.0,
    };

    // Store frame info
    this->position = position;
    this->size = size;
    this->z_level = z_level;
    this->id = menu_renderer->add(Surface(vertices, 2, glm::vec2(0.0), this->z_level, texture));
}

glm::vec2 Frame::get_position() {
    return this->position;
}

glm::vec2 Frame::get_size() {
    return this->size;
}

int Frame::get_z_level() {
    return this->z_level;
}

void Frame::toggle_display() {
    this->display = !this->display;
    MenuRenderer::get_instance()->get_surface(this->id - 1)->toggle_display();
}

bool Frame::should_display() {
    return this->display;
}