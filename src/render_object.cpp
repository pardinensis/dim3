#include "render_object.hpp"

#include "gl_utils.hpp"
#include "texture.hpp"
#include "shader.hpp"

std::map<std::string, RenderObject*> render_map;


RenderObject::RenderObject(const std::string& name) :
		ibuf_id(0), n_vertices(0), n_indices(0), material_name("NULL") {

	model_matrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
}


void RenderObject::add_vertex_buffer(BufferType type, GLenum content_type, 
		unsigned int n_vertices, unsigned int dim, const void* data, unsigned int layout_pos) {
	glBindVertexArray(vao_id);

	if (this->n_vertices == 0) {
		this->n_vertices = n_vertices;
	} else if (this->n_vertices != n_vertices) {
		std::stringstream ss;
		ss << "add_vertex_buffer failed: wrong number of vertices, got ";
		ss << n_vertices << ", expected " << this->n_vertices;
		throw ss.str();
	}

	GLuint buf_id;
	glGenBuffers(1, &buf_id);
	vbufs[type] = std::make_pair(buf_id, layout_pos);

	unsigned int size_in_bytes = size_of_gl_type(content_type) * dim * n_vertices;

	glBindBuffer(GL_ARRAY_BUFFER, buf_id);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(layout_pos);
	glVertexAttribPointer(layout_pos, dim, content_type, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

void RenderObject::add_vertex_buffer(BufferType type, const std::vector<glm::vec2>& v, 
		unsigned int layout_pos) {
	add_vertex_buffer(type, GL_FLOAT, v.size(), 2, &v[0], layout_pos);
}

void RenderObject::add_vertex_buffer(BufferType type, const std::vector<glm::vec3>& v,
		unsigned int layout_pos) {
	add_vertex_buffer(type, GL_FLOAT, v.size(), 3, &v[0], layout_pos);
	if (type == BufferType::POS) {
		create_bounding_box(v);
	}
}

void RenderObject::add_vertex_buffer(BufferType type, const std::vector<glm::vec4>& v,
		unsigned int layout_pos) {
	add_vertex_buffer(type, GL_FLOAT, v.size(), 4, &v[0], layout_pos);
}


void RenderObject::add_index_buffer(const std::vector<unsigned int>& v) {
	n_indices = v.size();

	glBindVertexArray(vao_id);

	glGenBuffers(1, &ibuf_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n_indices,
		&v[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void RenderObject::add_index_buffer(const std::vector<glm::uvec3>& v) {
	n_indices = 3 * v.size();

	glBindVertexArray(vao_id);
	
	glGenBuffers(1, &ibuf_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n_indices,
		&v[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void RenderObject::create_bounding_box(const std::vector<glm::vec3>& vs) {
	assert(vs.size() > 0);
	aabb_min = vs[0];
	aabb_max = vs[0];
	for (glm::vec3 v : vs) {
		if (v.x < aabb_min.x)
			aabb_min.x = v.x;
		if (v.x > aabb_max.x) 
			aabb_max.x = v.x;
		if (v.y < aabb_min.y)
			aabb_min.y = v.y;
		if (v.y > aabb_max.y) 
			aabb_max.y = v.y;
		if (v.z < aabb_min.z)
			aabb_min.z = v.z;
		if (v.z > aabb_max.z) 
			aabb_max.z = v.z;
	}
}

std::pair<glm::vec3, glm::vec3> RenderObject::get_bounding_box() {
	return std::make_pair(aabb_min, aabb_max);
}

void RenderObject::get_model(glm::mat4& model) {
	model = model_matrix;
}


void RenderObject::draw() {
	// bind vao
	glBindVertexArray(vao_id);
	
	// draw stuff
	if (ibuf_id) {
		glDrawElements(GL_TRIANGLES, n_indices, GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, n_vertices);
	}
		
	// unbind everything
	glBindVertexArray(0);
}

void RenderObject::set_material(const std::string& name) {
	material_name = name;
}

const std::string& RenderObject::get_material() {
	return material_name;
}


RenderObject::~RenderObject() {
	for (auto vbo_lpos : vbufs) {
		glDeleteBuffers(1, &vbo_lpos.first);
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