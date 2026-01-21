#ifndef PROJECTION
#define PROJECTION

#include <glm/glm.hpp>
#include <vector>

#include "../gl.h"
#include "../render/mesh.hpp"
using namespace std;

class Projector {
    public:
        static Projector* get_instance();

        // Projector should not be cloneable
        Projector(Projector& other) = delete;

        // Projector should not be assignable
        void operator=(const Projector&) = delete;

        // Getters
        glm::mat4 get_view_projection();

        // Setters
        void set_view_projection(glm::mat4 view);

    private:
        Projector();
        static Projector* instance;

        glm::mat4 projection;
        glm::mat4 view_projection;
        float fov = 45.0;
};

#endif
