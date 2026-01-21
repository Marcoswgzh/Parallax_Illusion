#ifndef SURFACE
#define SURFACE

#include <glm/glm.hpp>
#include <vector>
using namespace std;

#include "../texture/texture.hpp"

class Surface {
    public:
        Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level);
        Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level, Texture texture);

        // Getters
        vector<float>* get_vertices();
        int get_n_triangles();
        glm::vec2 get_position();
        int get_z_level();
        bool should_display();
        bool is_loaded();
        std::optional<Texture> get_texture();
        unsigned int* get_vbo();
        unsigned int* get_vao();


        // Setter
        void set_loaded(bool status);

        // Toggle
        void toggle_display();

    private:
        // Surface properties
        vector<float> vertices;
        int n_triangles;
        glm::vec2 position;
        int z_level;
        std::optional<Texture> texture;

        // Surface states
        bool display = true;
        bool loaded = false;

        // Surface buffers
        unsigned int VBO, VAO;
};

#endif
