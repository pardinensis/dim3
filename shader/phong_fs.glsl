#version 330 core

in vec3 var_wpos;
in vec3 var_wnorm; 


// material properties
uniform vec3 color;
uniform float reflectivity;
uniform float shininess;

// camera properties
uniform vec3 cam_wpos;

// point lights
#define MAX_POINT_LIGHTS 3
uniform vec3 pl_pos[MAX_POINT_LIGHTS];
uniform float pl_radius[MAX_POINT_LIGHTS];
uniform vec4 pl_col[MAX_POINT_LIGHTS];
uniform int n_pl;

out vec4 out_col;


void main() {
	vec3 ambient = vec3(0.05);
	vec3 debug_col = vec3(-1);

	float intensities[MAX_POINT_LIGHTS];
	for (int i = 0; i < n_pl; ++i) {
		vec3 dir = pl_pos[i] - var_wpos;
		float falloff_coeff = sqrt(2)/pl_radius[i];
		float falloff = falloff_coeff * length(dir);
		intensities[i] = 1/(falloff * falloff);
	}


	vec3 diffuse = vec3(0, 0, 0);
	for (int i = 0; i < n_pl; ++i) {
		vec3 dir = pl_pos[i] - var_wpos;
		float ndotl = max(0, dot(normalize(var_wnorm), normalize(dir)));

		// distance-falloff * angle-falloff * light-strength * light-color
		diffuse += intensities[i] * ndotl * pl_col[i].w * pl_col[i].xyz;
	}
	diffuse = diffuse * color;

	float i_spec = 0;
	for (int i = 0; i < n_pl; ++i) {
		vec3 to_light = normalize(pl_pos[i] - var_wpos);
		vec3 reflected = normalize(2 * dot(to_light, var_wnorm) * var_wnorm - to_light);
		vec3 to_cam = normalize(cam_wpos - var_wpos);
		//debug_col = normalize(reflected);
		i_spec += intensities[i] * pow(max(0, dot(reflected, to_cam)), shininess);
	}
	vec3 specular = i_spec * reflectivity * vec3(1);
	

	out_col = vec4(ambient + diffuse + specular, 1);

	if (debug_col != vec3(-1))
		out_col = vec4(debug_col, 1);
}