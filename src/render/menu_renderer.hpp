#ifndef MENU_RENDERER
#define MENU_RENDERER

#include <vector>

#include "../gl.h"
#include "../shaders/shaders.hpp"
#include "renderer.hpp"
using namespace std;

class MenuRenderer : public Renderer {
    public:
        static MenuRenderer* get_instance(GLFWwindow* window);

        // Scene renderer should not be cloneable
        MenuRenderer(MenuRenderer& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const MenuRenderer&) = delete;

        void draw() override;

    private:
        MenuRenderer(GLFWwindow* window);
        vector<float> get_flattened();
        void update() override;

        // Initialize shaders
        Shader shader = Shader("vertex_shader_2d.glsl", "fragmentation_shader.glsl");

        static MenuRenderer* instance;

        // TODO: Temporary window pointer
        GLFWwindow* window;
};

#endif