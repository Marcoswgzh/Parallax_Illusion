#ifndef FRAME
#define FRAME

#include <glm/glm.hpp>
#include "../render/mesh.hpp"
#include "../render/surface.hpp"

class Frame {
    public:
        // Overloaded constructor to allow for frames with colors or textures
        Frame(glm::vec2 position, glm::vec2 size, glm::vec3 color, int z_level);
        Frame(glm::vec2 position, glm::vec2 size, Texture texture, int z_level);

        // Toggle
        void toggle_display();

        // Getter
        glm::vec2 get_position();
        glm::vec2 get_size();
        int get_z_level();
        bool should_display();

    private:
        // Frame properties
        glm::vec2 position;
        glm::vec2 size;
        int z_level;
        int id;

        // Toggle state
        bool display = true;
};

#endif
