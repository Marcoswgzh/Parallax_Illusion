#ifndef SHADER
#define SHADER

#include <glm/glm.hpp>
#include <string>

#include "../gl.h"
using namespace std;

class Shader {
    public:
        Shader(const char* vs_path, const char* fs_path);
        Shader(const char* vs_path, const char* gs_path, const char* fs_path);
        void set_mat4(const char* name, const glm::mat4& value);
        void set_vec3(const char* name, const glm::vec3& value);
        void use();

    private:
        unsigned int shader_id;

        string read_shader(const char* path);
        unsigned int load(string header_source, GLenum shader_type);
};

#endif