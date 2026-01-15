#ifndef SCENE_RENDERER
#define SCENE_RENDERER

#include <vector>

#include "../camera/camera.hpp"
#include "../gl.h"
#include "../shaders/shaders.hpp"
#include "renderer.hpp"
using namespace std;

// 0: Ambient
// 1: Diffusion
// 2: Phong
enum LightType { Ambient = 0, Diffusion = 1, Phong = 2 };

class SceneRenderer : public Renderer {
    public:
        static SceneRenderer* get_instance();

        // Scene renderer should not be cloneable
        SceneRenderer(SceneRenderer& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const SceneRenderer&) = delete;

        void draw() override;

        void set_light_type(LightType type);

    private:
        SceneRenderer();
        void update_colored_mesh(Mesh mesh);
        void update_textured_mesh(Mesh mesh);
        void update() override;
        vector<int> get_flattened_indices();

        // Initialize shaders
        Shader color_shader =
            Shader("3D/color/shader.vert.glsl", "3D/color/shader.geo.glsl", "3D/color/shader.frag.glsl");
        Shader texture_shader =
            Shader("3D/texture/shader.vert.glsl", "3D/texture/shader.geo.glsl", "3D/texture/shader.frag.glsl");

        Camera camera;

        LightType light_type;

        static SceneRenderer* instance;
};

#endif