#pragma once

#include "common.hpp"
#include <glm/vec4.hpp>

class Renderer {
private:
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Renderer* renderer;


public:
	Renderer(SDL_Window* window);
	void render();
};