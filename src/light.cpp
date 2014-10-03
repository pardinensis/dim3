#include "light.hpp"

#include "shader.hpp"

#include <array>
#include <vector>


Light::Light(Type type, const glm::vec3& pos, const glm::vec3& dir, float radius, const glm::vec3& color,
		float inner_angle, float outer_angle) :
	type(type), pos(pos), dir(dir), radius(radius), color(color),
	inner_angle(inner_angle), outer_angle(outer_angle) {}



std::array<std::vector<Light*>, Light::Type::num_light_types> lights;


Light* create_pointlight(const glm::vec3& pos, float radius, const glm::vec3& color) {
	return new Light(Light::Type::POINT, pos, glm::vec3(0, 0, 0), radius, color, 0, 0);
}

Light* create_spotlight(const glm::vec3& pos, const glm::vec3& dir, float radius, const glm::vec3& color,
		float inner_angle, float outer_angle) {
	return new Light(Light::Type::SPOT, pos, dir, radius, color, inner_angle, outer_angle);
}

Light* create_globallight(const glm::vec3& dir, const glm::vec3& color) {
	return new Light(Light::Type::GLOBAL, glm::vec3(0, 0, 0), dir, 0, color, 0, 0);
}

void add_light(Light* light) {
	lights[light->type].push_back(light);
}

void bind_lights_to_shader(GLuint shader_id) {
	//point lights
	const std::vector<Light*>& point_lights = lights[Light::Type::POINT];
	int n_pl = point_lights.size();
	if (n_pl) {
		float pl_pos[3 * n_pl], pl_radius[n_pl], pl_col[3 * n_pl];
		for (int i = 0; i < n_pl; ++i) {
			Light* l = point_lights[i];
			pl_pos[3 * i + 0] = l->pos.x;
			pl_pos[3 * i + 1] = l->pos.y;
			pl_pos[3 * i + 2] = l->pos.z;
			pl_radius[i] = l->radius;
			pl_col[3 * i + 0] = l->color.x;
			pl_col[3 * i + 1] = l->color.y;
			pl_col[3 * i + 2] = l->color.z;
		}
		glUniform3fv(shader::uniform(shader_id, "pl_pos"), n_pl, pl_pos);
		glUniform1fv(shader::uniform(shader_id, "pl_radius"), n_pl, pl_radius);
		glUniform3fv(shader::uniform(shader_id, "pl_col"), n_pl, pl_col);
		glUniform1i(shader::uniform(shader_id, "n_pl"), n_pl);
	}
}