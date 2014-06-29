#include "renderer.hpp"

#include <GL/gl.h>
#include <map>
#include "file_utils.hpp"
#include "shader.hpp"
#include "texture.hpp"


std::map<std::string, RenderObject*> renderables;

Renderer::Renderer(SDL_Window* window) : window(window), context(nullptr), sdl_renderer(nullptr) {
	// init opengl context
	context = SDL_GL_CreateContext(window);
	check_sdl_error(context, "SDL_GL_CreateContext");
	push_cleanup_function(std::bind(SDL_GL_DeleteContext, context));

	// init renderer
	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	check_sdl_error(sdl_renderer, "SDL_CreateRenderer");
	push_cleanup_function(std::bind(SDL_DestroyRenderer, sdl_renderer));

	// initializing SDL_image
	texture::init();



	// parse clear color
	glClearColor(
		get<double>("RENDERER_BACKGROUND_COLOR_R", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_G", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_B", 0), 1);
}


void Renderer::register_render_object(const std::string& name) {
	renderables.emplace(name, get_render_object(name));
}

void Renderer::deregister_render_object(const std::string& name) {
	renderables.erase(name);
}



void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader::use("test");
	for (auto pair : renderables) {
		RenderObject* obj = pair.second;
		glBindVertexArray(obj->vao_id);
		
		if (obj->tex_id) glBindTexture(GL_TEXTURE_2D, obj->tex_id);
		
		glDrawArrays(GL_TRIANGLES, 0, obj->n_vertices);
		
		if (obj->tex_id) glBindTexture(GL_TEXTURE_2D, 0);
	}

	SDL_GL_SwapWindow(window);
}