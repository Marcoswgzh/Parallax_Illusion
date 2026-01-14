#version 330 core

layout(triangles) in;
in vec3 v_color[];
in vec3 v_frag_position[];

layout(triangle_strip, max_vertices = 3) out;
out vec3 color;
out vec3 frag_position;
out vec3 normal;

uniform vec3 camera_position;

void main()
{
    vec3 pos_A = gl_in[0].gl_Position.xyz;
    vec3 pos_B = gl_in[1].gl_Position.xyz;
    vec3 pos_C = gl_in[2].gl_Position.xyz;

    vec3 AC = pos_A - pos_C;
    vec3 BC = pos_B - pos_C;

    // Calculate vector from point A to camera position
    vec3 A_to_cam = camera_position - pos_A;

    normal = cross(AC, BC) * -1;
    if (dot(normal, A_to_cam) < 0) {
        normal *= -1;
    }
    
    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        color = v_color[i];
        frag_position = v_frag_position[i];
        EmitVertex();
    }
    EndPrimitive();
}
