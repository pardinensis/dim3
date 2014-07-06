#pragma once

#include "common.hpp"
#include <map>
#include <GL/glew.h>

class Material {

protected:
	std::string shader_name;
	GLuint program_id;

public:
	virtual void bind() = 0;
	GLuint get_program_id();
};

void add_material(const std::string& name, Material* mat);
void remove_material(const std::string& name);
Material* get_material(const std::string& name);