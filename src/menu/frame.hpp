#ifndef FRAME
#define FRAME

#include <glm/glm.hpp>
#include "../render/mesh.hpp"
#include "../render/surface.hpp"

class Frame {
    public:
        Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color, int z_level);
        glm::vec2 get_position();
        glm::vec2 get_size();
        glm::vec3 get_color();

    private:
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        int id;

        Surface calculate_surface();
};

#endif