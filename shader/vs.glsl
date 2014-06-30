#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tc;
layout(location = 2) in vec3 in_col;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec2 var_tc;
out vec3 var_col;

void main() {
	gl_Position = proj_matrix * view_matrix * vec4(in_pos, 1);

	var_tc = in_tc;
	var_col = in_col;
}