#include "shaders.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../gl.h"
using namespace std;

string Shader::readShader(char const* path) {
    std::ifstream file(path);

    // Check if the file is found
    // TODO: Something weird happening here, couldn't find file, but correct
    // render
    if (!file) {
        cerr << "ERROR: Couldn't open file: " << path << endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::load(string shaderSource, GLenum shaderType) {
    const char* source = shaderSource.c_str();
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check if the shader compilation was succesful
    int success;
    int logLength = 512;
    char* infoLog = new char[logLength];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, logLength, NULL, infoLog);
        std::cout << "ERROR: Shader compilation failed: \n" << infoLog << std::endl;
    }

    return shader;
}

Shader::Shader(const char* vs_path, const char* fs_path) {
    string vertex_shader_source = readShader(vs_path);
    string fragmentation_shader_source = readShader(fs_path);

    unsigned int vertexShader = load(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragmentShader = load(fragmentation_shader_source, GL_FRAGMENT_SHADER);

    shaderId = glCreateProgram();
    glAttachShader(shaderId, vertexShader);
    glAttachShader(shaderId, fragmentShader);
    glLinkProgram(shaderId);

    // Check if linking the shader program was succesful
    int success;
    int logLength = 512;
    char* infoLog = new char[logLength];
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR: Linking shader program failed: \n" << infoLog << std::endl;
    }

    // Delete the shader objects, because we don't need them anymore (already
    // linked)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() { glUseProgram(shaderId); }