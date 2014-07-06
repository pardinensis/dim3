#pragma once

#include <map>
#include <vector>
#include <array>
#include <utility>
#include "common.hpp"
#include "camera.hpp"

#include <GL/glew.h>

class RenderObject {
public:
	enum BufferType {
		POS, NORM, TC, COLOR, TANGENT, BINORM, num_buffer_types
	};

private:
	// (vbo_id, layout_pos)[num_buffer_types]
	std::array<std::pair<GLuint, unsigned int>, BufferType::num_buffer_types> vbufs;

	GLuint vao_id;
	GLuint ibuf_id;
	unsigned int n_vertices;
	unsigned int n_indices;

	std::string material_name;
	glm::mat4 model_matrix;

public:
	RenderObject(const std::string& name);
	~RenderObject();


	void add_vertex_buffer(BufferType type, GLenum content_type, 
		unsigned int n_vertices, unsigned int dim, const void* data, unsigned int layout_pos);
	void add_vertex_buffer(BufferType type, std::vector<glm::vec2>& v, unsigned int layout_pos);
	void add_vertex_buffer(BufferType type, std::vector<glm::vec3>& v, unsigned int layout_pos);
	void add_vertex_buffer(BufferType type, std::vector<glm::vec4>& v, unsigned int layout_pos);

	void add_index_buffer(std::vector<unsigned int>& i);
	void add_index_buffer(std::vector<glm::uvec3>& i);

	void draw();

	void set_material(const std::string& name);
	const std::string& get_material();
};

RenderObject* create_render_object(const std::string& name);
RenderObject* get_render_object(const std::string& name);
void delete_render_object(const std::string& name);
