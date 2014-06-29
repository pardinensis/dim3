#version 330 core

in vec2 var_tc;

uniform sampler2D tex;

out vec4 out_col;

void main() {
	out_col.rgb = texture(tex, var_tc).rgb;
	out_col.a = 1.0;
}