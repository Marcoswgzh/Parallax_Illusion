#ifndef SCENE_RENDERER
#define SCENE_RENDERER

#include <vector>

#include "../gl.h"
#include "../shaders/shaders.hpp"
#include "renderer.hpp"
using namespace std;

class SceneRenderer : public Renderer {
    public:
        static SceneRenderer* get_instance();

        // Scene renderer should not be cloneable
        SceneRenderer(SceneRenderer& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const SceneRenderer&) = delete;

        void draw() override;

    private:
        SceneRenderer();
        void update_coloured_mesh(Mesh mesh);
        void update_textured_mesh(Mesh mesh);
        void update() override;
        vector<int> get_flattened_indices();

        // Initialize shaders
        Shader colour_shader = Shader("colour/vertex_shader.vert.glsl", "colour/fragmentation_shader.frag.glsl");
        Shader texture_shader = Shader("texture/vertex_shader.vert.glsl", "texture/fragmentation_shader.frag.glsl");

        static SceneRenderer* instance;
};

#endif