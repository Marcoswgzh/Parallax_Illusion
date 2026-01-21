#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <optional>
#include "../render/scene_renderer.hpp"

Model::Model(std::string path, glm::vec3 position) {

    Assimp::Importer import;

    // Triangulate: Make every mesh a triangle in case we get non-triangle meshes.
    // Flip UVs: Flips textures in their y-axis, saves us the effort of doing it for OpenGL's coordinate system.
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Checks if:
    // 1. There were no import errors ('scene' is a valid pointer).
    // 2. The scene is complete (not missing any required data).
    // 3. If the root node is not null (which is apparently something that can happen?).
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("ERROR::ASSIMP::%s\n", import.GetErrorString());
        return;
    }

    // Record directory the obj file is in such that we can import its textures (required to be in the same directory).
    this->directory = path.substr(0, path.find_last_of('/'));

    // Create required Meshes
    processNode(scene->mRootNode, scene, position);

    // Add generated Meshes to Renderer
    for (Mesh& mesh : this->meshes) {
        this->ids.push_back(SceneRenderer::get_instance()->add(mesh));
    }
}

void Model::processNode(aiNode* node, const aiScene* scene, glm::vec3 position) {
    // get all the meshes from assimp's structure and store them in our own structure for later
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // Gets the index of mesh 'i' into the list of meshes imported by assimp, then uses that index to read the mesh from 'mMeshes'.
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        this->meshes.push_back(processMesh(mesh, scene, position));			
    }

    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, position);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, glm::vec3 position) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    // Texture Detection, the vertex array needs to be formatted differently depending on whether textures are present or not.
    bool hasTexture = false;
    std::string texturePath = "";
    aiColor3D diffuseColour(1.0f, 1.0f, 1.0f); // Default colour is white if no colour data is found inside the obj file.

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Check for texture data
        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString textureFileName; // file name + extension, no path
            material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFileName);
            texturePath = this->directory + "/" + textureFileName.C_Str();
            hasTexture = true;
        } 
        else {
            // If no texture is found, we will use the colour of the vertex instead.
            // If no colour info is present, material->Get() will not modify diffuseColour (default white)
            material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColour);
        }
    }

    // Build the Vertex Attribute Array
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        if (hasTexture) {
            // Textures are present, next two values are the UV coordinates.

            if (mesh->mTextureCoords[0]) {
                vertices.push_back(mesh->mTextureCoords[0][i].x);
                vertices.push_back(mesh->mTextureCoords[0][i].y);
            } else {
                // Fallback in case texture coordinates aren't present somehow.
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
            }

        } else {
            // Textures are not present, next three value are the RGB colour values.
            vertices.push_back(diffuseColour.r);
            vertices.push_back(diffuseColour.g);
            vertices.push_back(diffuseColour.b);
        }
    }

    // Create indices array, this information is already present in assimp we just need to put it into our array.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create the final Mesh.
    if (hasTexture) {
        // number of triangles = number of indices / 3, since assimp will triangulate all the meshes.
        return Mesh(vertices, indices, indices.size() / 3, position, Texture(texturePath));
    } else {
        // number of triangles = number of indices / 3, since assimp will triangulate all the meshes.
        return Mesh(vertices, indices, indices.size() / 3, position, std::nullopt);
    }
}
