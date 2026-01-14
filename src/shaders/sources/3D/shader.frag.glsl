#version 330 core

in vec3 color;
in vec3 frag_position;
in vec3 normal;
out vec4 fragmentation_color;

void main() {
    // TODO: Move to uniform block
    float ambient_strength = 0.5;
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 light_position = vec3(1.0f, 3.0f, 1.0f);
    vec3 ambient = ambient_strength * light_color;

    // Get light direction
    vec3 normal = normalize(normal);
    vec3 light_direction = normalize(light_position - frag_position);

    // Calculate diffusion
    float diffuse = max(dot(normal, light_direction), 0);
    vec3 diffusion = diffuse * light_color;

    vec3 result = (ambient + diffusion) * color;
    fragmentation_color = vec4(result, 1.0f);
}