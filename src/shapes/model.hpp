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

    private:
        // Private process methods
        void processNode(aiNode* node, const aiScene* scene, glm::vec3 position);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene, glm::vec3 position);

        vector<int> ids;
        std::string directory; // Path of the directory this Model is loaded from

        // Keep track of all meshes created by this model so they can possibly be re-used.
        std::vector<Mesh> meshes;
};

#endif
