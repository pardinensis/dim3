#include "camera.hpp"

#include <map>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera() {
	view_matrix = glm::mat4(1.0);
	proj_matrix = glm::mat4(1.0);
}

Camera::~Camera() {}



void Camera::set_lookat(glm::vec3& pos, glm::vec3& center, glm::vec3& up) {
	view_matrix = glm::lookAt(pos, center, up);
}

void Camera::set_perspective_projection(float fovy, float aspect, float near, float far) {
	proj_matrix = glm::perspective(fovy, aspect, near, far);
}

void Camera::set_orthographic_projection(float left, float right, 
		float bottom, float top, float near, float far) {
	proj_matrix = glm::ortho(left, right, bottom, top, near, far);
}



void Camera::upload_camera_matrices(GLuint view_loc, GLuint proj_loc) {
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj_matrix));
}

void Camera::upload_object_matrices(const glm::mat4& model_matrix, GLuint model_loc, GLuint normal_loc) {
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model_matrix * view_matrix)));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix3fv(normal_loc, 1, GL_FALSE, glm::value_ptr(normal_matrix));
}

void Camera::get_view(glm::mat4& view) {
	view = view_matrix;
}

void Camera::get_proj(glm::mat4& proj) {
	proj = proj_matrix;
}



std::map<std::string, Camera*> cam_map;

Camera* Camera::create(const std::string& name) {
	Camera* cam = new Camera;
	cam_map.emplace(name, cam);
	return cam;
}

Camera* Camera::get(const std::string& name) {
	auto it = cam_map.find(name);
	if (it != cam_map.end()) {
		return it->second;
	}
	std::stringstream ss;
	ss << "could not find camera " << name;
	throw ss.str();
}

void Camera::remove(const std::string& name) {
	auto it = cam_map.find(name);
	if (it != cam_map.end()) {
		delete it->second;
		cam_map.erase(it);
	}	
}

void Camera::remove_all() {
	for (auto p : cam_map) {
		delete p.second;
	}
	cam_map.clear();
}