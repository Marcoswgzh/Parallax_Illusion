#include "apple_cube.hpp"

#include "../render/mesh.hpp"
#include "../render/scene_renderer.hpp"
#include <optional>

AppleCube::AppleCube(glm::vec3 dimensions, glm::vec3 position) {

    // Last two elements of each row are texture coordinates, as opposed to last three being the colour information in cube.cpp.
    vector<float> vertices = {

        // Front side
        0.0f,         0.0f,         0.0f,         0.0f,         1.0f, // (index 0) Front lower left corner

        dimensions.x, 0.0f,         0.0f,         1.0f,         1.0f, // (1) Front lower right corner

        0.0f,         dimensions.y, 0.0f,         0.0f,         0.0f, // (2) Front higher left corner

        dimensions.x, dimensions.y, 0.0f,         1.0f,         0.0f, // (3) Front higher right corner


        // Left side
        0.0f,         0.0f,         dimensions.z, 0.0f,         1.0f, // (4) Back lower left corner

        0.0f,         0.0f,         0.0f,         1.0f,         1.0f, // (5) Front lower left corner

        0.0f,         dimensions.y, dimensions.z, 0.0f,         0.0f, // (6) Back higher left corner

        0.0f,         dimensions.y, 0.0f,         1.0f,         0.0f, // (7) Front higher left corner


        // Back side
        0.0f,         0.0f,         dimensions.z, 0.0f,         1.0f, // (8) Back lower left corner

        dimensions.x, 0.0f,         dimensions.z, 1.0f,         1.0f, // (9) Back lower right corner

        0.0f,         dimensions.y, dimensions.z, 0.0f,         0.0f, // (10) Back higher left corner

        dimensions.x, dimensions.y, dimensions.z, 1.0f,         0.0f, // (11) Back higher right corner


        // Right side
        dimensions.x, 0.0f,         dimensions.z, 0.0f,         1.0f, // (12) Back lower right corner

        dimensions.x, 0.0f,         0.0f,         1.0f,         1.0f, // (13) Front lower right corner

        dimensions.x, dimensions.y, dimensions.z, 0.0f,         0.0f, // (14) Back higher right corner

        dimensions.x, dimensions.y, 0.0f,         1.0f,         0.0f, // (15) Front higher right corner


        // Under side
        0.0f,         0.0f,         dimensions.z, 0.0f,         1.0f, // (16) Back lower left corner

        dimensions.x, 0.0f,         dimensions.z, 1.0f,         1.0f, // (17) Back lower right corner

        0.0f,         0.0f,         0.0f,         0.0f,         0.0f, // (18) Front lower left corner

        dimensions.x, 0.0f,         0.0f,         1.0f,         0.0f, // (19) Front lower right corner


        // Upper side
        0.0f,         dimensions.y, dimensions.z, 0.0f,         1.0f, // (20) Back higher left corner

        dimensions.x, dimensions.y, dimensions.z, 1.0f,         1.0f, // (21) Back higher right corner

        0.0f,         dimensions.y, 0.0f,         0.0f,         0.0f, // (22) Front higher left corner

        dimensions.x, dimensions.y, 0.0f,         1.0f,         0.0f, // (23) Front higher right corner
    };

    vector<int> indices = {
        // Front side
        0, 1, 3, // Right Triangle
        0, 3, 2, // Left Triangle

        // Left side
        4, 5, 7, // Right Triangle
        4, 7, 6, // Left Triangle

        // Back side
        8, 9, 11, // Left Triangle
        8, 11, 10, // Right Triangle

        // Right side
        12, 13, 15, // Left Triangle
        12, 14, 15, // Right Triangle

        // Under side
        16, 17, 19, // Left Triangle
        16, 18, 19, // Right Triangle

        // Upper side
        20, 21, 23, // Left Triangle
        20, 22, 23 // Right Triangle
    };

    Mesh mesh(vertices, indices, 12, position, Texture("textures/apple_skin.png"));

    this->id = SceneRenderer::get_instance()->add(mesh);
}

// TODO: Implement
float AppleCube::get_volume() {}
float AppleCube::get_width() {}
float AppleCube::get_height() {}
float AppleCube::get_depth() {}