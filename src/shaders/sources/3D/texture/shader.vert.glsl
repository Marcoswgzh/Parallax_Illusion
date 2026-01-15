#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;
out vec2 v_texture_coordinates;
out vec3 v_frag_position;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(position, 1.0);
    v_frag_position = position;
    v_texture_coordinates = texture_coordinates;
}