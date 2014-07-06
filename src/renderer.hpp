#pragma once

#include "common.hpp"
#include "render_object.hpp"
#include "material.hpp"
#include "camera.hpp"
#include <glm/vec4.hpp>

class Renderer {
private:
	SDL_Window* window;
	SDL_GLContext context;

	std::string camera;

public:
	SDL_Renderer* sdl_renderer;


public:
	Renderer(SDL_Window* window);

	void register_render_object(RenderObject* obj);
	void deregister_render_object(RenderObject* obj);

	void register_material(Material* mat);
	void deregister_material(Material* mat);

	void set_camera(const std::string& name);

	void render();
};