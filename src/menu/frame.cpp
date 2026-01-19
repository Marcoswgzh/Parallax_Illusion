#include <iostream>

#include "frame.hpp"
#include "../render/menu_renderer.hpp"

Frame::Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color, int z_level) {
    MenuRenderer* menu_renderer = MenuRenderer::get_instance();

    // Store frame info
    this->position = position;
    this->size = size;
    this->color = color;
    this->z_level = z_level;
    this->id = menu_renderer->add(this->calculate_surface());
}

Surface Frame::calculate_surface() {
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

    return Surface(vertices, 2, glm::vec2(0.0), this->z_level);
}

glm::vec2 Frame::get_position() {
    return this->position;
}

glm::vec2 Frame::get_size() {
    return this->size;
}

glm::vec3 Frame::get_color() {
    return this->color;
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