#include "material.hpp"

#include "texture.hpp"
#include "shader.hpp"

GLuint Material::get_program_id() {
	return program_id;
}

std::map<std::string, Material*> matmap;

void add_material(const std::string& name, Material* mat) {
	matmap.emplace(name, mat);
}

void remove_material(const std::string& name) {
	auto it = matmap.find(name);
	if (it != matmap.end()) {
		matmap.erase(it);
	}
}

Material* get_material(const std::string& name) {
	auto it = matmap.find(name);
	if (it != matmap.end()) {
		return it->second;
	}
	std::stringstream ss;
	ss << "could not find material " << name;
	throw ss.str();
}



// ===== Phong =====

PhongMaterial::PhongMaterial(glm::vec3 color, float reflectivity, float shininess) :
		color(color), reflectivity(reflectivity), shininess(shininess) {

	static bool initialized = false;
	if (!initialized) {
		shader::create("phong", "shader/pos_norm_vs.glsl", GL_VERTEX_SHADER);
		shader::create("phong", "shader/pos_norm_fs.glsl", GL_FRAGMENT_SHADER);
		initialized = true;
	}
}

void PhongMaterial::bind() {
	program_id = shader::use("phong");
	glUniform3f(shader::uniform(program_id, "color"), color.x, color.y, color.z);
	glUniform1f(shader::uniform(program_id, "reflectivity"), reflectivity);
	glUniform1f(shader::uniform(program_id, "shininess"), shininess);
}


// ===== Textured Phong =====

TexturedPhongMaterial::TexturedPhongMaterial(const std::string& texture_name, 
											 float reflectivity, float shininess) :
		texture_name(texture_name), reflectivity(reflectivity), shininess(shininess) {

	static bool initialized = false;
	if (!initialized) {
		shader::create("texturedphong", "shader/pos_norm_tc_vs.glsl", GL_VERTEX_SHADER);
		shader::create("texturedphong", "shader/pos_norm_tc_fs.glsl", GL_FRAGMENT_SHADER);
		initialized = true;
	}
}

void TexturedPhongMaterial::bind() {
	program_id = shader::use("texturedphong");
	glUniform1i(shader::uniform(program_id, "diffuse_texture"), texture::get(texture_name));
	glUniform1f(shader::uniform(program_id, "reflectivity"), reflectivity);
	glUniform1f(shader::uniform(program_id, "shininess"), shininess);
}


// ===== Debug Normals =====

NormalsMaterial::NormalsMaterial() {
	static bool initialized = false;
	if (!initialized) {
		shader::create("normals", "shader/normals_vs.glsl", GL_VERTEX_SHADER);
		shader::create("normals", "shader/normals_gs.glsl", GL_GEOMETRY_SHADER);
		shader::create("normals", "shader/normals_fs.glsl", GL_FRAGMENT_SHADER);
		initialized = true;
	}
}

void NormalsMaterial::bind() {
	program_id = shader::use("normals");
}