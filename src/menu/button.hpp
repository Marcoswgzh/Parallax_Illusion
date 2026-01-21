#ifndef BUTTON
#define BUTTON

#include <glm/glm.hpp>

#include "frame.hpp"

class Button : public Frame {
    public:
        // Overloaded constructor to allow for frames with colors or textures
        Button(Frame frame, glm::vec2 position, glm::vec2 size, glm::vec3 color);
        Button(Frame frame, glm::vec2 position, glm::vec2 size, Texture texture);

        // General
        bool contains(glm::vec2 point);

    private:
        // Private calculation
        glm::vec2 get_relative_position(Frame frame, glm::vec2 position);
};

#endif