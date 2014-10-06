#pragma once

#include "common.hpp"

#include <GL/gl.h>


namespace texture {
	void init();

	void create(const std::string& name, const std::string& filename);
	void remove(const std::string& name);
	void remove_all();

	GLuint get(const std::string& name);
}