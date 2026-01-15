#ifndef SCENE_RENDERER
#define SCENE_RENDERER

#include <vector>

#include "../camera/camera.hpp"
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
        Shader color_shader =
            Shader("3D/color/shader.vert.glsl", "3D/color/shader.geo.glsl", "3D/color/shader.frag.glsl");
        Shader texture_shader =
            Shader("3D/texture/shader.vert.glsl", "3D/texture/shader.geo.glsl", "3D/texture/shader.frag.glsl");

        Camera camera;

        static SceneRenderer* instance;
};

#endif