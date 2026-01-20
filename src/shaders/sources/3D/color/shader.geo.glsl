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
    // Use the world space positions (not the projected positions from gl_in)
    vec3 pos_A = v_frag_position[0].xyz;
    vec3 pos_B = v_frag_position[1].xyz;
    vec3 pos_C = v_frag_position[2].xyz;

    vec3 CA = pos_A - pos_C;
    vec3 CB = pos_B - pos_C;
    normal = cross(CA, CB);

    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        color = v_color[i];
        frag_position = v_frag_position[i];
        EmitVertex();
    }
    EndPrimitive();
}
