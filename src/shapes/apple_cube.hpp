#ifndef APPLE_CUBE
#define APPLE_CUBE

#include "../gl.h"
#include "../render/mesh.hpp"
#include "shape3D.hpp"
#include "../texture/Texture.hpp"

/**
 * Cube shape.
 */
class AppleCube : public Shape3D {
    public:
        AppleCube(glm::vec3 dimensions, glm::vec3 position);

    private:
};

#endif