#version 330 core

layout(triangles) in;
in vec3 v_color[];
in vec3 v_frag_position[];

layout(triangle_strip, max_vertices = 3) out;
out vec3 color;
out vec3 frag_position;
out vec3 normal;

void main()
{
    vec3 posA = gl_in[0].gl_Position.xyz;
    vec3 posB = gl_in[1].gl_Position.xyz;
    vec3 posC = gl_in[2].gl_Position.xyz;

    vec3 AC = posA - posC;
    vec3 BC = posB - posC;
    normal = cross(AC, BC);

    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        color = v_color[i];
        frag_position = v_frag_position[i];
        EmitVertex();
    }
    EndPrimitive();
}
