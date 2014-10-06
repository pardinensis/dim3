#pragma once
#include "material.hpp"

#include "common.hpp"

class PhongMaterial : public Material {
private:
	glm::vec3 color;
	float reflectivity;
	float shininess;

public:
	PhongMaterial(glm::vec3 color, float reflectivity, float shininess);

	virtual void bind();
};