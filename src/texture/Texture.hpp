#ifndef TEXTURE
#define TEXTURE

#include <string>

class Texture {
    public:
        Texture(std::string image_path);

        // Getters
        std::string get_image_path();
        int get_texture_id();

    private:
        std::string image_path;
        int texture_id;
};

#endif
