#pragma once

#include <GL/glew.h>
#include <string>

namespace shader {
	void create(const std::string& name, const std::string& filename, GLuint type);
	void remove(const std::string& name);
	void remove_all();

	GLuint use(const std::string& name);

	GLuint uniform(GLuint program_id, const std::string& name);
}