#include <stb_image.h>
#include <glm/glm.hpp>
#include <glad.h>
#include <iostream>

#include "texture.hpp"

/**
 * Texture constructor it generates and stores a texture.
 */
Texture::Texture(std::string image_path) {
    this->image_path = image_path;

    // Read the data
    int width, height, channel_count;
    unsigned char *data = stbi_load(image_path.c_str(), &width, &height, &channel_count, 0);

    // Check if the data is loaded correctly
    if (data == nullptr) {
        printf("Failed to load texture %s!\n", image_path.c_str());
    }

    // Create a texture
    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    // Bind the texture so the following commands work on our newly created texture
    glBindTexture(GL_TEXTURE_2D, texture_id);

    GLint internal_format;
    if (channel_count == 4) {
        internal_format = GL_RGBA;
    } else {
        // Assume 3 channels.
        internal_format = GL_RGB;
    } 

    // Actually generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, data);

    // Generate required mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // We're done with the actual texture data itself, so we can free it.
    stbi_image_free(data);

    this->texture_id = texture_id;
}

/**
 * Gets the texture id.
 */
int Texture::get_texture_id() {
    return this->texture_id;
}

/**
 * Gets the 
 */
std::string Texture::get_image_path() {
    return this->image_path;
}
