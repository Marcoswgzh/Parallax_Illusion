#include "button.hpp"

Button::Button(Frame frame, glm::vec2 position, glm::vec2 size, glm::vec3 color) : Frame(this->get_relative_position(frame, position), size, color, frame.get_z_level() + 1) {}
Button::Button(Frame frame, glm::vec2 position, glm::vec2 size, Texture texture) : Frame(this->get_relative_position(frame, position), size, texture, frame.get_z_level() + 1) {}

glm::vec2 Button::get_relative_position(Frame frame, glm::vec2 position) {
    return frame.get_position() + position;
}

bool Button::contains(glm::vec2 point) {
    if (point.x > this->get_position().x && point.x < this->get_position().x + this->get_size().x &&
        point.y > this->get_position().y && point.y < this->get_position().y + this->get_size().y) {
        return true;
    }

    return false;
}