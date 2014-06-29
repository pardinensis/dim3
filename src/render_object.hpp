#pragma once

#include <map>
#include <vector>
#include <utility>
#include "common.hpp"

#include <GL/glew.h>

class RenderObject {
private:
	// name -> (vbo_id, layout_pos)
	std::map<std::string, std::pair<GLuint, unsigned int>> vbufs;

public:
	GLuint vao_id;
	unsigned int n_vertices;
	unsigned int n_indices;


public:
	RenderObject(const std::string& name);
	~RenderObject();


	void add_vertex_buffer(const std::string& name, GLenum content_type, 
		unsigned int n_vertices, unsigned int dim, const void* data, unsigned int layout_pos);
	void add_vertex_buffer(const std::string& name, std::vector<glm::vec2>& v, unsigned int layout_pos);
	void add_vertex_buffer(const std::string& name, std::vector<glm::vec3>& v, unsigned int layout_pos);
	void add_vertex_buffer(const std::string& name, std::vector<glm::vec4>& v, unsigned int layout_pos);

};

RenderObject* create_render_object(const std::string& name);
RenderObject* get_render_object(const std::string& name);
void delete_render_object(const std::string& name);
