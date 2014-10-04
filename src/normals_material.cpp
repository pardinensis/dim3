#include "normals_material.hpp"
#include "shader.hpp"


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
