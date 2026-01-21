#ifndef SHADER
#define SHADER

#include <glm/glm.hpp>
#include <string>

#include "../gl.h"
using namespace std;

class Shader {
    public:
        // Overloaded constructor to allow for a shader with or without a geometry shader
        Shader(const char* vs_path, const char* fs_path);
        Shader(const char* vs_path, const char* gs_path, const char* fs_path);

        // General
        void use();

        // Setteres
        void set_mat4(const char* name, const glm::mat4& value);
        void set_vec3(const char* name, const glm::vec3& value);
        void set_int(const char* name, int value);

    private:
        // Private general
        string read_shader(const char* path);
        unsigned int load(string header_source, GLenum shader_type);

        unsigned int shader_id;
};

#endif
