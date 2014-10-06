#pragma once

#include "common.hpp"
#include <vector>

unsigned int size_of_gl_type(GLenum type);

void create_cube_vertex_buffer(std::vector<glm::vec3>& v);
void create_cube_index_buffer(std::vector<glm::uvec3>& v);

void create_plane_vertex_buffer(std::vector<glm::vec3>& v, float size, float height);
void create_plane_index_buffer(std::vector<glm::uvec3>& v);

void convert_to_triangle_soup(std::vector<glm::vec3>& verts, std::vector<glm::uvec3>& tris);

void calculate_face_normals(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
	std::vector<glm::vec3>& normals);
void calculate_vertex_normals_by_area(const std::vector<glm::vec3>& verts,
	const std::vector<glm::uvec3>& tris, std::vector<glm::vec3>& normals);
void calculate_vertex_normals_by_angle(const std::vector<glm::vec3>& verts,
	const std::vector<glm::uvec3>& tris, std::vector<glm::vec3>& normals);