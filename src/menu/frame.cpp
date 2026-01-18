#include "frame.hpp"
#include "../render/menu_renderer.hpp"

Frame::Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color) {
    MenuRenderer* menu_renderer = MenuRenderer::get_instance();

    // Store frame info
    this->position = position;
    this->size = size;
    this->color = color;
    this->id = menu_renderer->add(this->calculate_mesh());
}

Mesh Frame::calculate_mesh() {
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

    return Mesh(vertices, {}, 2, glm::vec3(0.0), std::nullopt);
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
