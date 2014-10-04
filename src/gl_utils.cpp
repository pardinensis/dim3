#include "gl_utils.hpp"

#include <glm/gtx/vector_angle.hpp>

#include "common.hpp"

unsigned int size_of_gl_type(GLenum type) {
	switch(type) {
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_INT:
			return sizeof(GLint);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		default:
			std::stringstream ss;
			ss << "size_of_gl_type failed: unknown GL type " << type;
			throw ss.str();
	}
}

void create_cube_vertex_buffer(std::vector<glm::vec3>& v) {
	v = {
		glm::vec3(-1,  1, -1),
		glm::vec3( 1,  1, -1),
		glm::vec3(-1, -1, -1),
		glm::vec3( 1, -1, -1),
		glm::vec3(-1,  1,  1),
		glm::vec3( 1,  1,  1),
		glm::vec3(-1, -1,  1),
		glm::vec3( 1, -1,  1)
	};
}

void create_cube_index_buffer(std::vector<glm::uvec3>& v) {
	v = {
		glm::uvec3(0, 1, 2), //front
		glm::uvec3(2, 1, 3),
		glm::uvec3(5, 4, 7), //back
		glm::uvec3(7, 4, 6),
		glm::uvec3(1, 5, 3), //right
		glm::uvec3(3, 5, 7),
		glm::uvec3(4, 0, 6), //left
		glm::uvec3(6, 0, 2),
		glm::uvec3(4, 5, 0), //top
		glm::uvec3(0, 5, 1),
		glm::uvec3(2, 3, 6), //bottom
		glm::uvec3(6, 3, 7)
	};
}

void create_plane_vertex_buffer(std::vector<glm::vec3>& v, float size, float height) {
	v = {
		glm::vec3(-size, height, -size),
		glm::vec3(-size, height,  size),
		glm::vec3( size, height, -size),
		glm::vec3( size, height,  size)
	};
}

void create_plane_index_buffer(std::vector<glm::uvec3>& v) {
	v = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(2, 1, 3)
	};
}

void convert_to_triangle_soup(std::vector<glm::vec3>& verts, std::vector<glm::uvec3>& tris) {
	std::vector<glm::vec3> old_verts = verts;
	std::vector<glm::uvec3> old_tris = tris;
	verts.clear();
	tris.clear();
	for (unsigned int i = 0; i < old_tris.size(); ++i) {
		verts.push_back(old_verts[old_tris[i].x]);
		verts.push_back(old_verts[old_tris[i].y]);
		verts.push_back(old_verts[old_tris[i].z]);
		tris.push_back(glm::uvec3(3*i, 3*i+1, 3*i+2));
	}
}

void calculate_face_normals(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
					std::vector<glm::vec3>& normals) {
	normals.clear();
	for (glm::uvec3 t : tris) {
		normals.push_back(glm::normalize(glm::cross(verts[t.y] - verts[t.x], verts[t.z] - verts[t.x])));
	}
}

void calculate_vertex_normals_by_area(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
					   std::vector<glm::vec3>& normals) {
	normals.clear();
	for (unsigned int i = 0; i < verts.size(); ++i) {
		normals.push_back(glm::vec3(0, 0, 0));
	}
	for (glm::uvec3 t : tris) {
		glm::vec3 n = glm::cross(verts[t.y] - verts[t.x], verts[t.z] - verts[t.x]);
		normals[t.x] += n;
		normals[t.y] += n;
		normals[t.z] += n;
	}
	for (unsigned int i = 0; i < verts.size(); ++i) {
		normals[i] = glm::normalize(normals[i]);
		std::cout << "TRI " << normals[i] << std::endl;
	}
}

void calculate_vertex_normals_by_angle(const std::vector<glm::vec3>& verts, const std::vector<glm::uvec3>& tris,
					   std::vector<glm::vec3>& normals) {
	normals.clear();
	for (unsigned int i = 0; i < verts.size(); ++i) {
		normals.push_back(glm::vec3(0, 0, 0));
	}
	for (glm::uvec3 t : tris) {
		glm::vec3 a = glm::normalize(verts[t.y] - verts[t.x]);
		glm::vec3 b = glm::normalize(verts[t.z] - verts[t.y]);
		glm::vec3 c = glm::normalize(verts[t.x] - verts[t.z]);
		glm::vec3 n = glm::normalize(glm::cross(a, b));
		normals[t.x] += n * glm::angle(-c, a);
		normals[t.y] += n * glm::angle(-a, b);
		normals[t.z] += n * glm::angle(-b, c);
	}
	for (unsigned int i = 0; i < verts.size(); ++i) {
		normals[i] = glm::normalize(normals[i]);
	}
}