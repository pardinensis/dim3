#version 330 core

in data {
	vec4 color;
} gdata;

out vec4 out_color;

void main() {
	out_color = gdata.color;
}