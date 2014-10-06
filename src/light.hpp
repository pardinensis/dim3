#pragma once

#include "common.hpp"

class Light {
public:
	enum Type {
		POINT, SPOT, GLOBAL, num_light_types
	} type;

protected:
	glm::vec3 pos;		// POINT  SPOT
	glm::vec3 dir;		//        SPOT  GLOBAL
	float radius; 		// POINT  SPOT
	glm::vec4 color;	// POINT  SPOT  GLOBAL
	float inner_angle;	//        SPOT
	float outer_angle;	//        SPOT

protected:
	Light(Type type, const glm::vec3& pos, const glm::vec3& dir, float radius, const glm::vec4& color,
		float inner_angle, float outer_angle);

	friend Light* create_pointlight(const glm::vec3& pos, float radius, const glm::vec4& color);
	friend Light* create_spotlight(const glm::vec3& pos, const glm::vec3& dir, float radius,
		const glm::vec4& color, float inner_angle, float outer_angle);
	friend Light* create_globallight(const glm::vec3& dir, const glm::vec4& color);
	friend void bind_lights_to_shader(GLuint shader_id);
};

Light* create_pointlight(const glm::vec3& pos, float radius, const glm::vec4& color);
Light* create_spotlight(const glm::vec3& pos, const glm::vec3& dir, float radius,
	const glm::vec4& color, float inner_angle, float outer_angle);
Light* create_globallight(const glm::vec3& dir, const glm::vec4& color);


void add_light(Light* light);
void bind_lights_to_shader(GLuint shader_id);