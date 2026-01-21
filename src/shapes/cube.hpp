#ifndef CUBE
#define CUBE

#include "../gl.h"
#include "../render/mesh.hpp"
#include "shape3D.hpp"

/**
 * Cube shape.
 */
class Cube : public Shape3D {
    public:
        Cube(glm::vec3 dimensions, glm::vec3 position, glm::vec3 color);

    private:
};

#endif
