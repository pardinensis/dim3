#pragma once

#include "common.hpp"
#include <vector>

unsigned int size_of_gl_type(GLenum type);

void create_cube_vertex_buffer(std::vector<glm::vec3>& v);
void create_cube_index_buffer(std::vector<glm::uvec3>& v);

void calculate_face_normals(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
	std::vector<glm::vec3>& normals);
void calculate_vertex_normals(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
	std::vector<glm::vec3>& normals);