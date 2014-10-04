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
	// positions
	vec4 wpos = model_matrix * vec4(in_pos, 1);
	vec4 epos = proj_matrix * view_matrix * wpos;
	gl_Position = epos;
	var_wpos = wpos.xyz;

	// normals
	var_wnorm = in_norm;
}