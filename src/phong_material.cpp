#include "phong_material.hpp"
#include "shader.hpp"


PhongMaterial::PhongMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
		ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {

	static bool initialized = false;
	if (!initialized) {
		shader::create("phong", "shader/phong_vs.glsl", GL_VERTEX_SHADER);
		shader::create("phong", "shader/phong_fs.glsl", GL_FRAGMENT_SHADER);
		initialized = true;
	}
}

void PhongMaterial::bind() {
	program_id = shader::use("phong");
	glUniform3f(shader::uniform(program_id, "ambient"), ambient.x, ambient.y, ambient.z);
	glUniform3f(shader::uniform(program_id, "diffuse"), diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(shader::uniform(program_id, "specular"), specular.x, specular.y, specular.z);
	glUniform1f(shader::uniform(program_id, "shininess"), shininess);
}
