#version 330 core
#include shader/phong_lighting.glsl

in vec3 var_wpos;
in vec3 var_wnorm;

// material properties
uniform vec3 color;
uniform float reflectivity;
uniform float shininess;

// camera properties
uniform vec3 cam_wpos;

out vec4 out_col;

void main() {
	out_col = phong(var_wpos, var_wnorm, color, cam_wpos, reflectivity, shininess);
}