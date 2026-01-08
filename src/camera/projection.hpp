#ifndef PROJECTION
#define PROJECTION

#include <glm/glm.hpp>
#include <vector>

#include "../gl.h"
#include "../render/mesh.hpp"
#include "../render/renderer.hpp"
using namespace std;

class Projector {
    public:
        static Projector* get_instance();

        // Projector should not be cloneable
        Projector(Projector& other) = delete;

        // Projector should not be assignable
        void operator=(const Projector&) = delete;

        void set_view_projection(glm::mat4 view);
        vector<float> project_list(vector<Mesh> objects, int n_triangles);

    private:
        Projector();
        static Projector* instance;

        glm::mat4 projection;
        glm::mat4 view_projection;
};

#endif