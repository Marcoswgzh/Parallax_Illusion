#ifndef SHADER
#define SHADER

#include <string>

#include "../gl.h"
using namespace std;

class Shader {
    public:
        Shader(const char* vs_path, const char* fs_path);
        void use();

    private:
        const char* vertex_shader_source;
        const char* fragmentation_shader_source;
        unsigned int shaderId;

        string readShader(const char* path);
        unsigned int load(string headerSource, GLenum shaderType);
};

#endif