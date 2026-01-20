#ifndef TEXTURE
#define TEXTURE

#include <string>

class Texture {
    public:
        Texture(std::string imagePath);

        std::string get_imagePath();
        int get_textureID();

    private:
        std::string imagePath;
        int textureID;
};

#endif