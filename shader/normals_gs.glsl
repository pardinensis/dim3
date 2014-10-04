#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices=10) out;

in vec3 var_wpos[3];
in vec3 var_wnorm[3];

uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out data {
	vec4 color;
} gdata;

void main() {
	for (int i = 0; i < 3; ++i) {
		gl_Position = proj_matrix * view_matrix * vec4(var_wpos[i], 1);
		gdata.color = vec4(0, 1, 0, 1);
		EmitVertex();

		gl_Position = proj_matrix * view_matrix * vec4(var_wpos[i] + var_wnorm[i], 1);
		gdata.color = vec4(0, 0, 1, 1);
		EmitVertex();

		EndPrimitive();
	}
	for (int i = 0; i < 4; ++i) {
		gl_Position = proj_matrix * view_matrix * vec4(var_wpos[i%3], 1);
		gdata.color = vec4(1, 0, 0, 1);
		EmitVertex();
	}
	EndPrimitive();
}