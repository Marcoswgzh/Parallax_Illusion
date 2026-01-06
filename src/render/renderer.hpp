#ifndef RENDERER
#define RENDERER

#include <vector>

#include "Mesh.hpp"
using namespace std;

class Renderer {
    public:
        // Avoid leaks
        virtual ~Renderer() = default;

        int add(Mesh mesh);
        void remove(int index, int n_triangles);
        virtual void draw() = 0;

    protected:
        virtual void update() = 0;

        unsigned int VAO;
        bool change;          // Tracks changes in the visual objects
        int n_triangles;      // Total amount of triangles in the renderer
        vector<Mesh> meshes;  // All the meshes in the renderer
};

#endif