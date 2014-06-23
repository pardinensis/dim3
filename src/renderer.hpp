#pragma once

#include "shared.hpp"
#include <glm/vec4.hpp>

class Renderer {
private:
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Renderer* renderer;

	glm::vec4 clear_color;

public:
	Renderer(SDL_Window* window);
	void render();
};