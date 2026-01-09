#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class Mesh {
    public:
        Mesh(vector<float> vertices, vector<int> indices, int n_triangles, glm::vec3 position, std::optional<int> textureID);

        vector<float>* get_vertices();
        vector<int>* get_indices();
        int get_n_triangles();
        glm::vec3 get_position();
        std::optional<int> get_textureID();

    private:
        vector<float> vertices;
        vector<int> indices;
        int n_triangles;
        glm::vec3 position;

        std::optional<int> textureID;
};

#endif