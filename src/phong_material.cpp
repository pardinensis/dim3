#include "phong_material.hpp"
#include "shader.hpp"


PhongMaterial::PhongMaterial(glm::vec3 color, float reflectivity, float shininess) :
		color(color), reflectivity(reflectivity), shininess(shininess) {

	static bool initialized = false;
	if (!initialized) {
		shader::create("phong", "shader/phong_vs.glsl", GL_VERTEX_SHADER);
		shader::create("phong", "shader/phong_fs.glsl", GL_FRAGMENT_SHADER);
		initialized = true;
	}
}

void PhongMaterial::bind() {
	program_id = shader::use("phong");
	glUniform3f(shader::uniform(program_id, "color"), color.x, color.y, color.z);
	glUniform1f(shader::uniform(program_id, "reflectivity"), reflectivity);
	glUniform1f(shader::uniform(program_id, "shininess"), shininess);
}
