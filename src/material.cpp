#include "material.hpp"

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