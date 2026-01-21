#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 in_color;
out vec3 color;

uniform int z_level;

void main() {
    float z = -1.0 + 0.0001 / z_level;
    gl_Position = vec4(position, z, 1.0);
    color = in_color;
}
