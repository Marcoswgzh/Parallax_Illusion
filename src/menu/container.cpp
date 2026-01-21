#include "container.hpp"

Container::Container(optional<Frame> frame, glm::vec2 position, glm::vec2 size, glm::vec3 color) : 
Frame(this->get_relative_position(frame, position), size, color, this->calculate_z_level(frame)) {}

glm::vec2 Container::get_relative_position(std::optional<Frame> frame, glm::vec2 position) {
    if (!frame.has_value()) {
        return position;
    }

    return frame.value().get_position() + position;
}

int Container::calculate_z_level(std::optional<Frame> frame) {
    if (!frame.has_value()) {
        return 1;
    }

    return frame.value().get_z_level() + 1;
}
