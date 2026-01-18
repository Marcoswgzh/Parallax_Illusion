#ifndef FRAME
#define FRAME

#include <glm/glm.hpp>
#include "../render/mesh.hpp"

class Frame {
    public:
        Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color);
        glm::vec2 get_position();
        glm::vec2 get_size();
        glm::vec3 get_color();

    private:
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        int id;

        Mesh calculate_mesh();
};

#endif