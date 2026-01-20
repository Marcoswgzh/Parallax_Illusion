#ifndef FRAME
#define FRAME

#include <glm/glm.hpp>
#include "../render/mesh.hpp"
#include "../render/surface.hpp"

class Frame {
    public:
        Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color, int z_level);
        Frame(glm::vec2 position, glm::vec2 size, Texture texture, int z_level);

        glm::vec2 get_position();
        glm::vec2 get_size();
        int get_z_level();
        void toggle_display();
        bool should_display();

    private:
        glm::vec2 position;
        glm::vec2 size;
        int z_level;
        int id;
        bool display = true;
};

#endif