#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_norm;

uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec3 var_wpos;
out vec3 var_wnorm; 

void main() {
	vec4 wpos = model_matrix * vec4(in_pos, 1);
	vec4 epos = view_matrix * wpos;
	vec4 spos = proj_matrix * epos;

	gl_Position = spos;

	var_wpos = wpos.xyz;
	var_wnorm = in_norm;
}