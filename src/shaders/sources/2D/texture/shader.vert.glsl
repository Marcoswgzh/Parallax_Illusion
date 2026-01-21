#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coordinates;
out vec2 v_texture_coordinates;

uniform int z_level;

void main() {
    float z = -1.0 + 0.0001 / z_level;
    gl_Position = vec4(position, z, 1.0);
    v_texture_coordinates = texture_coordinates;
}
