#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include <vector>
#include <optional>
using namespace std;

#include "../texture/texture.hpp"

class Mesh {
    public:
        Mesh(vector<float> vertices, vector<unsigned int> indices, int n_triangles, glm::vec3 position, std::optional<Texture> texture);

        // Getters
        vector<float> get_positioned_vertices(int offset);
        vector<float>* get_vertices();
        vector<unsigned int>* get_indices();
        int get_n_triangles();
        glm::vec3 get_position();
        std::optional<Texture> get_texture();
        bool is_loaded();

        // Setter
        void set_loaded(bool status);

        unsigned int VBO, EBO, VAO; // TODO: Make getters for these values (if possible)

    private:
        // Mesh properties
        vector<float> vertices;
        vector<unsigned int> indices;
        int n_triangles;
        glm::vec3 position;
        std::optional<Texture> texture;

        // Mesh state
        bool loaded = false;
};

#endif
