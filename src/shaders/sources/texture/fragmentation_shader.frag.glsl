#version 330 core

in vec2 textureCoords;
out vec4 fragmentation_color;

void main() {
    fragmentation_color = vec4(vec3(1,0,0), 1.0f);
}