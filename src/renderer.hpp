#pragma once

#include "common.hpp"
#include "render_object.hpp"
#include <glm/vec4.hpp>

class Renderer {
private:
	SDL_Window* window;
	SDL_GLContext context;

public:
	SDL_Renderer* sdl_renderer;


public:
	Renderer(SDL_Window* window);

	void register_render_object(const std::string& name);
	void deregister_render_object(const std::string& name);

	void render();
};