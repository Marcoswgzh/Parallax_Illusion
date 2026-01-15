#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class Mesh {
    public:
        Mesh(vector<float> vertices, vector<int> indices, int n_triangles, glm::vec3 position);

        vector<float>* get_vertices();
        vector<int>* get_indices();
        int get_n_triangles();
        glm::vec3 get_position();
        vector<float> get_positioned_vertices();

    private:
        vector<float> vertices;
        vector<int> indices;
        int n_triangles;
        glm::vec3 position;
};

#endif