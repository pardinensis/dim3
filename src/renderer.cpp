#include "renderer.hpp"

#include <GL/gl.h>
#include <map>
#include "file_utils.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "texture.hpp"


std::map<std::string, std::vector<RenderObject*>> renderables;

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

	// gl settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	// parse clear color
	glClearColor(
		get<double>("RENDERER_BACKGROUND_COLOR_R", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_G", 0),
		get<double>("RENDERER_BACKGROUND_COLOR_B", 0), 1);
}


void Renderer::register_render_object(RenderObject* obj) {
	auto it = renderables.find(obj->get_material());
	if (it == renderables.end()) {
		it = renderables.emplace(obj->get_material(), std::vector<RenderObject*>()).first;
	}
	it->second.push_back(obj);
}

void Renderer::deregister_render_object(RenderObject* obj) {
	auto& vec = renderables.find(obj->get_material())->second;
	for (auto it2 = vec.begin(); it2 != vec.end(); ++it2) {
		if (*it2 == obj) {
			vec.erase(it2);
		}
	}
}


void Renderer::set_camera(const std::string& name) {
	camera = name;
}



void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Camera* cam = Camera::get(camera);
	
	for (auto pair : renderables) {
		// bind material
		Material* mat = get_material(pair.first);
		mat->bind();

		// get shader locations
		GLuint program_id = mat->get_program_id();
		GLuint model_loc = shader::uniform(program_id, "model_matrix");
		GLuint normal_loc = shader::uniform(program_id, "normal_matrix");
		GLuint view_loc = shader::uniform(program_id, "view_matrix");
		GLuint proj_loc = shader::uniform(program_id, "proj_matrix");

		// pass camera matrices
		cam->upload_camera_matrices(view_loc, proj_loc);

		// pass light information
		bind_lights_to_shader(program_id);

		// draw all objects with this material		
		for (RenderObject* obj : pair.second) {
			// pass camera matrices
			glm::mat4 model;
			obj->get_model(model);
			cam->upload_object_matrices(model, model_loc, normal_loc);

			obj->draw();
		}
	}

	SDL_GL_SwapWindow(window);
}