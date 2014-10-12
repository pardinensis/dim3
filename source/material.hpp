#pragma once

#include "common.hpp"
#include <map>

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


// MATERIALS

class PhongMaterial : public Material {
private:
	glm::vec3 color;
	float reflectivity;
	float shininess;

public:
	PhongMaterial(glm::vec3 color, float reflectivity, float shininess);
	virtual void bind();
};

class TexturedPhongMaterial : public Material {
private:
	std::string texture_name;
	float reflectivity;
	float shininess;

public:
	TexturedPhongMaterial(const std::string& texture_name, float reflectivity, float shininess);
	virtual void bind();
};

class NormalsMaterial : public Material {
public:
	NormalsMaterial();
	virtual void bind();
};