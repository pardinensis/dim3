#version 330 core

in vec3 var_wpos;
in vec3 var_wnorm;

// material properties
uniform vec3 color;
uniform float reflectivity;
uniform float shininess;

// point lights
#define MAX_POINT_LIGHTS 3
uniform vec3 pl_pos[MAX_POINT_LIGHTS];
uniform float pl_radius[MAX_POINT_LIGHTS];
uniform vec3 pl_col[MAX_POINT_LIGHTS];
uniform int n_pl;

out vec4 out_col;



void main() {
	vec3 ambient = vec3(0.05, 0.05, 0.05);

	vec3 diffuse = vec3(0, 0, 0);
	for (int i = 0; i < n_pl; ++i) {
		vec3 dir = pl_pos[i] - var_wpos;
		float ndotl = max(0, dot(normalize(var_wnorm), normalize(dir)));
		float falloff_coeff = sqrt(2)/pl_radius[i];
		float falloff = falloff_coeff * length(dir);
		float intensity = 1/(falloff * falloff);

		diffuse += intensity * ndotl * pl_col[i];
	}
	diffuse = diffuse * color;

	out_col = vec4(ambient + diffuse, 1);

}