#version 330

uniform vec3 u_view_pos;
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec4 a_color;

out vec3 a_coord;
out vec3 normal;
out vec4 color;

void main()
{
    color = a_color;
	gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
    a_coord = vec3(u_m_matrix * vec4(a_position,1.0));

    normal = (u_m_matrix * vec4(a_normal, 0.0)).xyz;    
}