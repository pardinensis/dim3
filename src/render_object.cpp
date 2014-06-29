#include "render_object.hpp"

#include "gl_utils.hpp"

std::map<std::string, RenderObject*> render_map;


RenderObject::RenderObject(const std::string& name) :
		n_vertices(0), n_indices(0) {

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
}


void RenderObject::add_vertex_buffer(const std::string& name, GLenum content_type, 
		unsigned int n_vertices, unsigned int dim, const void* data, unsigned int layout_pos) {
	glBindVertexArray(vao_id);

	this->n_vertices = n_vertices;

	GLuint buf_id;
	glGenBuffers(1, &buf_id);
	vbufs.emplace(name, std::make_pair(buf_id, layout_pos));

	unsigned int size_in_bytes = size_of_gl_type(content_type) * dim * n_vertices;

	glBindBuffer(GL_ARRAY_BUFFER, buf_id);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(layout_pos);
	glVertexAttribPointer(layout_pos, dim, content_type, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}
void RenderObject::add_vertex_buffer(const std::string& name, std::vector<glm::vec2>& v, 
		unsigned int layout_pos) {
	add_vertex_buffer(name, GL_FLOAT, v.size(), 2, &v[0], layout_pos);
}
void RenderObject::add_vertex_buffer(const std::string& name, std::vector<glm::vec3>& v,
		unsigned int layout_pos) {
	add_vertex_buffer(name, GL_FLOAT, v.size(), 3, &v[0], layout_pos);
}
void RenderObject::add_vertex_buffer(const std::string& name, std::vector<glm::vec4>& v,
		unsigned int layout_pos) {
	add_vertex_buffer(name, GL_FLOAT, v.size(), 4, &v[0], layout_pos);
}

RenderObject::~RenderObject() {
	for (auto pair : vbufs) {
		glDeleteBuffers(1, &pair.second.first);
	}
	glDeleteVertexArrays(1, &vao_id);
}



RenderObject* create_render_object(const std::string& name) {
	RenderObject* obj = new RenderObject(name);
	render_map.emplace(name, obj);

	return obj;
}

RenderObject* get_render_object(const std::string& name) {
	auto it = render_map.find(name);
	if (it != render_map.end()) {
		return it->second;
	} else {
		std::stringstream ss;
		ss << "could not find RenderObject " << name;
		throw ss.str();
	}
}

void delete_render_object(const std::string& name) {
	auto it = render_map.find(name);
	if (it != render_map.end()) {
		delete it->second;
		render_map.erase(it);
	}
}