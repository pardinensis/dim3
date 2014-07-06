#pragma once
#include "material.hpp"

#include "common.hpp"

#include <GL/glew.h>

class PhongMaterial : public Material {
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

public:
	PhongMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	virtual void bind();
};