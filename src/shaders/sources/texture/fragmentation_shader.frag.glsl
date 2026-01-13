#version 330 core

in vec2 textureCoords;
out vec4 finalColour;

uniform sampler2D meshTexture;

void main() {
    finalColour = texture(meshTexture, textureCoords);
}