#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texture_coordinates;
out vec2 v_texture_coordinates;
out vec3 v_frag_position;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(aPos, 1.0);
    v_frag_position = aPos;
    v_texture_coordinates = texture_coordinates;
}