#ifndef MENU_RENDERER
#define MENU_RENDERER

#include <vector>

#include "../gl.h"
#include "../shaders/shaders.hpp"
#include "surface.hpp"
using namespace std;

class MenuRenderer {
    public:
        static MenuRenderer* get_instance();

        // Scene renderer should not be cloneable
        MenuRenderer(MenuRenderer& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const MenuRenderer&) = delete;

        int add(Surface surface);
        Surface* get_surface(int index);
        void draw();

    private:
        static MenuRenderer* instance;

        MenuRenderer();
        vector<float> get_flattened_vertices();
        void update();
        void update_surface(Surface surface);

        // Initialize shaders
        Shader shader = Shader("2D/shader.vert.glsl", "2D/shader.frag.glsl");

        unsigned int VAO;
        int n_triangles;           // Total amount of triangles in the renderer
        vector<Surface> surfaces;  // All the meshes in the renderer
};

#endif