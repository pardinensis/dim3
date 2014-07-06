#version 330 core

layout(location = 0) in vec3 in_pos;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec3 var_wpos;

void main() {
	vec4 wpos = vec4(in_pos, 1); //TODO: model matrix
	vec4 epos = proj_matrix * view_matrix * wpos;

	gl_Position = epos;
	var_wpos = wpos.xyz;
}