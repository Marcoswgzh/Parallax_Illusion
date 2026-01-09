#include "apple_cube.hpp"

#include "../render/mesh.hpp"
#include "../render/scene_renderer.hpp"
#include <optional>

AppleCube::AppleCube(glm::vec3 dimensions, glm::vec3 position, Texture texture) {

    // Last two elements of each row are texture coordinates, as opposed to last three being the colour information in Cube.cpp.
    vector<float> vertices = {
        0.0f,         0.0f,         0.0f,         0.0f,         0.0f,

        0.0f,         dimensions.y, 0.0f,         0.0f,         1.0f,  

        dimensions.x, dimensions.y, 0.0f,         1.0f,         1.0f,

        dimensions.x, 0.0f,         0.0f,         1.0f,         0.0f,

        0.0f,         0.0f,         dimensions.z, 0.0f,         0.0f,

        0.0f,         dimensions.y, dimensions.z, 0.0f,         1.0f,

        dimensions.x, dimensions.y, dimensions.z, 1.0f,         1.0f,

        dimensions.x, 0.0f,         dimensions.z, 1.0f,         0.0f
    };

    vector<int> indices = {0, 1, 2, 0, 2, 3,

                           0, 1, 5, 0, 4, 5,

                           0, 3, 7, 0, 4, 7,

                           6, 1, 2, 6, 1, 5,

                           6, 2, 3, 6, 3, 7,

                           6, 4, 5, 6, 4, 7};

    Mesh mesh(vertices, indices, 12, position, texture);

    this->id = SceneRenderer::get_instance()->add(mesh);
}

// TODO: Implement
float AppleCube::get_volume() {}
float AppleCube::get_width() {}
float AppleCube::get_height() {}
float AppleCube::get_depth() {}