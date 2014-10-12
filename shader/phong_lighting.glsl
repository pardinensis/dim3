// point lights
#define MAX_POINT_LIGHTS 3
uniform vec3 pl_pos[MAX_POINT_LIGHTS];
uniform float pl_radius[MAX_POINT_LIGHTS];
uniform vec4 pl_col[MAX_POINT_LIGHTS];
uniform int n_pl;

vec4 phong(vec3 position, vec3 normal, vec3 color, vec3 camera_position, float reflectivity, float shininess) {
	float intensities[MAX_POINT_LIGHTS];
	for (int i = 0; i < n_pl; ++i) {
		vec3 dir = pl_pos[i] - position;
		float falloff_coeff = sqrt(2)/pl_radius[i];
		float falloff = falloff_coeff * length(dir);
		intensities[i] = 1/(falloff * falloff);
	}

	vec3 ambient = 0.05 * color;

	vec3 diffuse = vec3(0);
	for (int i = 0; i < n_pl; ++i) {
		vec3 dir = pl_pos[i] - position;
		float ndotl = max(0, dot(normalize(normal), normalize(dir)));

		// distance-falloff * angle-falloff * light-strength * light-color
		diffuse += intensities[i] * ndotl * pl_col[i].w * pl_col[i].xyz;
	}
	diffuse = diffuse * color;

	vec3 specular = vec3(0);
	for (int i = 0; i < n_pl; ++i) {
		vec3 to_light = normalize(pl_pos[i] - position);
		vec3 reflected = normalize(2 * dot(to_light, normal) * normal - to_light);
		vec3 to_cam = normalize(camera_position - position);
		//debug_col = normalize(reflected);
		float i_spec = pow(max(0, dot(reflected, to_cam)), shininess);
		specular += intensities[i] * i_spec * reflectivity * pl_col[i].w * pl_col[i].xyz;
	}
	specular *= color;
	
	return vec4(ambient + diffuse + specular, 1);
}