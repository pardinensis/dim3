#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tc;

out vec2 var_tc;

void main() {
	gl_Position.xyz = in_pos;
	gl_Position.w = 1.0;

	var_tc = in_tc;
}