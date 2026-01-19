#version 330 core

in vec2 v_texture_coordinates;
out vec4 fragmentation_color;

uniform sampler2D surface_texture;

void main() {
    vec4 tex = texture(surface_texture, v_texture_coordinates);

    // Discard if the alpha is 0 (transparent)
    if (tex.a == 0.0) {
        discard;
    }

    fragmentation_color = tex;
}