#ifndef SCENE_RENDERER
#define SCENE_RENDERER

#include <vector>

#include "../camera/camera.hpp"
#include "../gl.h"
#include "../shaders/shaders.hpp"
#include "mesh.hpp"
using namespace std;

// 0: Ambient
// 1: Diffusion
// 2: Phong
enum LightType { Ambient = 0, Diffusion = 1, Phong = 2 };

class SceneRenderer {
    public:
        static SceneRenderer* get_instance();

        // Scene renderer should not be cloneable
        SceneRenderer(SceneRenderer& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const SceneRenderer&) = delete;

        int add(Mesh mesh);
        void draw();
        void set_light_type(LightType type);

        void toggle_movement();
        void toggle_key_movement();

        void remove_current_scene();

    private:
        static SceneRenderer* instance;

        SceneRenderer();
        void update_mesh(Mesh* mesh, int offset);
        void update_colored_mesh(Mesh* mesh);
        void update_textured_mesh(Mesh* mesh);
        void update();

        // Initialize shaders
        Shader color_shader = Shader("3D/color/shader.vert.glsl", "3D/color/shader.geo.glsl", "3D/color/shader.frag.glsl");
        Shader texture_shader = Shader("3D/texture/shader.vert.glsl", "3D/texture/shader.geo.glsl", "3D/texture/shader.frag.glsl");

        // Scene variables
        Camera camera;
        LightType light_type;

        int n_triangles;      // Total amount of triangles in the renderer
        vector<Mesh> meshes;  // All the meshes in the renderer
};

#endif