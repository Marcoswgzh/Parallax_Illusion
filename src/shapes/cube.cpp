#include "cube.hpp"

#include "../render/mesh.hpp"
#include "../render/scene_renderer.hpp"

Cube::Cube(glm::vec3 dimensions, glm::vec3 position, glm::vec3 color) {
    vector<float> vertices = {
        0.0f,         0.0f,         0.0f,         color.x, color.y, color.z,

        0.0f,         dimensions.y, 0.0f,         color.x, color.y, color.z,

        dimensions.x, dimensions.y, 0.0f,         color.x, color.y, color.z,

        dimensions.x, 0.0f,         0.0f,         color.x, color.y, color.z,

        0.0f,         0.0f,         dimensions.z, color.x, color.y, color.z,

        0.0f,         dimensions.y, dimensions.z, color.x, color.y, color.z,

        dimensions.x, dimensions.y, dimensions.z, color.x, color.y, color.z,

        dimensions.x, 0.0f,         dimensions.z, color.x, color.y, color.z,
    };

    vector<int> indices = {0, 1, 2, 0, 2, 3,

                           0, 1, 5, 0, 4, 5,

                           0, 3, 7, 0, 4, 7,

                           6, 1, 2, 6, 1, 5,

                           6, 2, 3, 6, 3, 7,

                           6, 4, 5, 6, 4, 7};

    Mesh mesh(vertices, indices, 12, position);

    this->id = SceneRenderer::get_instance()->add(mesh);
}

// TODO: Implement
float Cube::get_width() {
    return 0.0;
}

float Cube::get_height() {
    return 0.0;
}

float Cube::get_depth() {
    return 0.0;
}