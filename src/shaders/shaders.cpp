#include "shaders.hpp"

#include <cstddef>
#include <fstream>
#include <glm/ext/matrix_float3x3.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "../gl.h"
using namespace std;

string Shader::read_shader(char const* path) {
    std::ifstream file(path);

    // Check if the file is found
    if (!file) {
        cerr << "ERROR: Couldn't open file: " << path << endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::load(string shader_source, GLenum shader_type) {
    const char* source = shader_source.c_str();
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check if the shader compilation was succesful
    int success;
    int log_length = 512;
    char* info_log = new char[log_length];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, log_length, NULL, info_log);
        std::cout << "ERROR: Shader compilation failed: \n" << info_log << std::endl;
    }

    return shader;
}

Shader::Shader(const char* vs_path, const char* fs_path) {
    // Get the shaders source text
    string vertex_shader_source = read_shader(vs_path);
    string fragmentation_shader_source = read_shader(fs_path);

    // Load shaders
    unsigned int vertex_shader = load(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = load(fragmentation_shader_source, GL_FRAGMENT_SHADER);

    this->shader_id = glCreateProgram();
    glAttachShader(this->shader_id, vertex_shader);
    glAttachShader(this->shader_id, fragment_shader);
    glLinkProgram(this->shader_id);

    // Check if linking the shader program was succesful
    int success;
    int log_length = 512;
    char* info_log = new char[log_length];
    glGetProgramiv(this->shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shader_id, 512, NULL, info_log);
        std::cout << "ERROR: Linking shader program failed: \n" << info_log << std::endl;
    }

    // Delete the shader objects, because we don't need them anymore (already linked)
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::Shader(const char* vs_path, const char* gs_path, const char* fs_path) {
    // Get the shaders source text
    string vertex_shader_source = this->read_shader(vs_path);
    string geometry_shader_source = this->read_shader(gs_path);
    string fragmentation_shader_source = this->read_shader(fs_path);

    // Load shaders
    unsigned int vertex_shader = this->load(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int geometry_shader = this->load(geometry_shader_source, GL_GEOMETRY_SHADER);
    unsigned int fragment_shader = this->load(fragmentation_shader_source, GL_FRAGMENT_SHADER);

    this->shader_id = glCreateProgram();
    glAttachShader(this->shader_id, vertex_shader);
    glAttachShader(this->shader_id, geometry_shader);
    glAttachShader(this->shader_id, fragment_shader);
    glLinkProgram(this->shader_id);

    // Check if linking the shader program was succesful
    int success;
    int log_length = 512;
    char* info_log = new char[log_length];
    glGetProgramiv(this->shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shader_id, 512, NULL, info_log);
        std::cout << "ERROR: Linking shader program failed: \n" << info_log << std::endl;
    }

    // Delete the shader objects, because we don't need them anymore (already linked)
    glDeleteShader(vertex_shader);
    glDeleteShader(geometry_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() { glUseProgram(shader_id); }

void Shader::set_mat4(const char* name, const glm::mat4& value) {
    int location = glGetUniformLocation(this->shader_id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::set_vec3(const char* name, const glm::vec3& value) {
    int location = glGetUniformLocation(this->shader_id, name);
    glUniform3fv(location, 1, &value[0]);
}

void Shader::set_int(const char* name, int value) {
    int location = glGetUniformLocation(this->shader_id, name);
    glUniform1i(location, value);
}
