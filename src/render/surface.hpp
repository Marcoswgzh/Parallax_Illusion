#ifndef SURFACE
#define SURFACE

#include <glm/glm.hpp>
#include <vector>
#include "../texture/Texture.hpp"
using namespace std;

class Surface {
    public:
        Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level);
        Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level, Texture texture);

        vector<float>* get_vertices();
        int get_n_triangles();
        glm::vec2 get_position();
        int get_z_level();
        void toggle_display();
        bool should_display();
        bool is_loaded();
        void set_loaded(bool status);

        unsigned int VBO, EBO, VAO;

        std::optional<Texture> get_texture();

    private:
        vector<float> vertices;
        int n_triangles;
        glm::vec2 position;
        int z_level;
        bool display = true;
        bool loaded = false;

        std::optional<Texture> texture;
};

#endif