#version 330 core

in vec4 var_wpos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;

out vec4 out_col;

void main() {
	vec3 tmp = diffuse + specular * shininess;
	out_col = vec4(ambient, 1);
}