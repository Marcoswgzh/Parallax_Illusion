#ifndef SURFACE
#define SURFACE

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class Surface {
    public:
        Surface(vector<float> vertices, int n_triangles, glm::vec2 position, int z_level);

        vector<float>* get_vertices();
        int get_n_triangles();
        glm::vec2 get_position();
        int get_z_level();
        void toggle_display();
        bool should_display();

    private:
        vector<float> vertices;
        int n_triangles;
        glm::vec2 position;
        int z_level;
        bool display = true;
};

#endif