#version 330 core

in vec3 color;
in vec3 frag_position;
in vec3 normal;
out vec4 fragmentation_color;

uniform vec3 camera_position;
uniform int light_type;
uniform vec3 light_position;
uniform vec3 light_color;

void main() {
    float ambient_strength = 0.5;
    float specular_strength = 0.6;
    vec3 ambient = ambient_strength * light_color;

    // Get light direction
    vec3 normal_direction;
    if (!gl_FrontFacing) {
        normal_direction = -normal;
    } else {
        normal_direction = normal;
    }

    vec3 normal = normalize(normal_direction);
    vec3 light_direction = normalize(frag_position - light_position);

    // Calculate diffusion
    float diffuse = max(dot(normal, light_direction) * -1.0, 0.0);
    vec3 diffusion = diffuse * light_color;

    // Calculate specular
    vec3 view_direction = normalize(frag_position - camera_position);
    vec3 reflect_direction = reflect(-light_direction, normal); 
    float specular_multiplier = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
    vec3 specular = specular_strength * specular_multiplier * light_color;  

    vec3 result;
    if (light_type == 0) {
        result = (ambient) * color;
    } else if (light_type == 1) {
        result = (ambient + diffusion) * color;
    } else {
        result = (ambient + diffusion + specular) * color;
    }

    fragmentation_color = vec4(result, 1.0f);
}