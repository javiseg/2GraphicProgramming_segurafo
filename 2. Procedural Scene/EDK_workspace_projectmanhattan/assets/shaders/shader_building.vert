#version 330

uniform float u_time;
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

out vec3 normal;
out float time;
out vec3 world_pos;
out vec2 uvs_;

void main() 
{
	uvs_ = a_uv;
    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
	world_pos = vec3(u_m_matrix * vec4(a_position, 1.0));
	
	normal = (u_m_matrix * vec4(a_normal,0.0)).xyz;
	//time = u_m_matrix[0].x * 10.0;
}