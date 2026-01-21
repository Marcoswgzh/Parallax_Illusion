#ifndef CONTAINER
#define CONTAINER

#include <glm/glm.hpp>
#include <optional>

#include "frame.hpp"
#include "button.hpp"

class Container : public Frame {
    public:
        Container(optional<Frame> frame, glm::vec2 position, glm::vec2 size, glm::vec3 color);

    private:
        // Private calculations
        glm::vec2 get_relative_position(std::optional<Frame> frame, glm::vec2 position);
        int calculate_z_level(std::optional<Frame> frame);
};

#endif
