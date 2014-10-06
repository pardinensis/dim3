#pragma once
#include "material.hpp"

#include "common.hpp"

class NormalsMaterial : public Material {
public:
	NormalsMaterial();

	virtual void bind();
};