#ifndef MESH
#define MESH

#include <vector>
using namespace std;

class Mesh {
    public:
        Mesh(vector<float> triangles, vector<int> indices, int n_triangles);

        vector<float>* get_triangles();
        vector<int>* get_indices();
        int get_n_triangles();

    private:
        vector<float> triangles;
        vector<int> indices;
        int n_triangles;
};

#endif