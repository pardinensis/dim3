#version 330 core
#include shader/phong_lighting.glsl

in vec3 var_wpos;
in vec3 var_wnorm;
in vec2 var_uv;

// material properties
uniform sampler2D diffuse_texture;
uniform float reflectivity;
uniform float shininess;

// camera properties
uniform vec3 cam_wpos;

out vec4 out_col;

void main() {
	vec3 color = texture(diffuse_texture, var_uv).rgb;
	out_col = phong(var_wpos, var_wnorm, color, cam_wpos, reflectivity, shininess);
}