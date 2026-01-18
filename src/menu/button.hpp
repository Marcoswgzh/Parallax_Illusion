#ifndef BUTTON
#define BUTTON

#include <glm/glm.hpp>

#include "frame.hpp"

class Button : public Frame {
    public:
        Button(Frame frame, glm::vec2 position, glm::vec2 size, glm::vec3 color);
        bool contains(glm::vec2 point);

    private:
        glm::vec2 get_relative_position(Frame frame, glm::vec2 position);
};

#endif