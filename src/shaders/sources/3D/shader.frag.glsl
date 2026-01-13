#version 330 core

in vec3 color;
in vec3 frag_position;
in vec3 normal;
out vec4 fragmentation_color;

void main() {
    fragmentation_color = vec4(color, 1.0f);
}