#include "Texture.hpp"

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glad.h>

Texture::Texture(std::string imagePath) {
    this->imagePath = imagePath;

    // Read the data
    int width, height, channelCount;
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &channelCount, 0);

    // Create a texture
    unsigned int textureID;
    glGenTextures(1, &textureID);

    // Bind the texture so the following commands work on our newly created texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Actually generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // We're done with the actual texture data itself, so we can free it.
    stbi_image_free(data);

    this->textureID = textureID;
}

int Texture::get_textureID() {
    return this->textureID;
}

std::string Texture::get_imagePath() {
    return this->imagePath;
}