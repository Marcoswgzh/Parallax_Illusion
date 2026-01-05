#ifndef RENDERER
#define RENDERER

#include <vector>
using namespace std;

struct VisualObject {
        vector<float> triangles;
        vector<int> indices;
        int n_triangles;
};

class Renderer {
    public:
        // Avoid leaks
        virtual ~Renderer() = default;

        int add(VisualObject object);
        void replace(int index, vector<float> triangles, int n_triangles, int n_previous_triangles);
        void remove(int index, int n_triangles);
        virtual void draw() = 0;

    protected:
        virtual void update() = 0;

        unsigned int VAO;
        bool change;  // Tracks changes in the visual objects
        int n_visual_objects;
        int n_triangles;
        vector<VisualObject> visual_objects;
};

#endif