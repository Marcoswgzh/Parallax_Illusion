#ifndef MODEL
#define MODEL

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include <assimp/scene.h>
#include "../render/mesh.hpp"

class Model {
    public:
        Model(std::string path, glm::vec3 position);

        // Keep track of all meshes created by this model so they can possibly be re-used.
        std::vector<Mesh> meshes;

    private:
        std::string directory; // Path of the directory this Model is loaded from

        void processNode(aiNode* node, const aiScene* scene, glm::vec3 position);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene, glm::vec3 position);
};

#endif