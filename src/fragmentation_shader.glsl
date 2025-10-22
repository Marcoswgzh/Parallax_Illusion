#version 330 core

in vec3 color;
out vec4 fragmentation_color;

void main() {
    fragmentation_color = vec4(color, 1.0f);
}