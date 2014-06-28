#include "renderer.hpp"

#include <GL/gl.h>
#include "fileutils.hpp"

Renderer::Renderer(SDL_Window* window) : window(window), context(nullptr), renderer(nullptr) {
	// init opengl context
	context = SDL_GL_CreateContext(window);
	check_sdl_error(context, "SDL_GL_CreateContext");
	push_cleanup_function(std::bind(SDL_GL_DeleteContext, context));

	// init renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	check_sdl_error(renderer, "SDL_CreateRenderer");
	push_cleanup_function(std::bind(SDL_DestroyRenderer, renderer));

	// parse clear color
	glClearColor(
		get<double>("RENDERER_BACKGROUND_COLOR_R", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_G", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_B", 0), 1);
}

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window);
}