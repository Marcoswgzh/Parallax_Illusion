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

        // General
        int add(Surface surface);
        void draw();

        // Getter
        Surface* get_surface(int index);

    private:
        MenuRenderer();
        static MenuRenderer* instance;

        // Update methods
        void update();
        void update_color_surface(Surface* surface);
        void update_texture_surface(Surface* surface);
        void update_surface(Surface* surface, int offset);

        // Initialize shaders
        Shader color_shader = Shader("2D/color/shader.vert.glsl", "2D/color/shader.frag.glsl");
        Shader texture_shader = Shader("2D/texture/shader.vert.glsl", "2D/texture/shader.frag.glsl");

        int n_triangles;           // Total amount of triangles in the renderer
        vector<Surface> surfaces;  // All the meshes in the renderer
};

#endif
