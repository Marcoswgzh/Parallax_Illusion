#include "Texture.hpp"

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glad.h>
#include <iostream>

Texture::Texture(std::string imagePath) {
    this->imagePath = imagePath;

    // Read the data
    int width, height, channelCount;
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &channelCount, 0);

    // Check if the data is loaded correctly
    if (data == nullptr) {
        printf("Failed to load texture %s!\n", imagePath.c_str());
    }

    // Create a texture
    unsigned int textureID;
    glGenTextures(1, &textureID);

    // Bind the texture so the following commands work on our newly created texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLint internalFormat;
    if (channelCount == 4) {
        internalFormat = GL_RGBA;
    } else {
        // Assume 3 channels.
        internalFormat = GL_RGB;
    } 

    // Actually generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);

    // Generate required mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

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
