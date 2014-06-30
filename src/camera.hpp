#pragma once

#include "common.hpp"
#include <GL/glew.h>

class Camera {

private:
	glm::mat4 view_matrix;
	glm::mat4 proj_matrix;

	Camera();
	~Camera();

public:
	void set_lookat(glm::vec3& pos, glm::vec3& center, glm::vec3& up);
	void set_perspective_projection(float fovy, float aspect, float near, float far);
	void set_orthographic_projection(float left, float right, float bottom, float top, 
			float near, float far);


	void upload_matrices(GLuint view_loc, GLuint proj_loc);

	void get_view(glm::mat4& view);
	void get_proj(glm::mat4& proj);

	static Camera* create(const std::string& name);
	static Camera* get(const std::string& name);
	static void remove(const std::string& name);
	static void remove_all();
};