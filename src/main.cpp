#include "file_utils.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "common.hpp"


SDL_Window* window = nullptr;
Renderer* renderer = nullptr;

bool should_quit = false;



void init() {
	parse_config_file("config.txt");

	// initializing SDL
	int success = SDL_Init(SDL_INIT_VIDEO);
	check_sdl_error(success, "SDL_Init");
	push_cleanup_function(SDL_Quit);

	// creating a window
	uint window_flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL;
	if (get<int>("WINDOW_FULLSCREEN", 0)) window_flags |= SDL_WINDOW_FULLSCREEN;
	if (get<int>("WINDOW_RESIZABLE", 0)) window_flags |= SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow(
		get<std::string>("WINDOW_NAME").c_str(),
		get<int>("WINDOW_POS_X", SDL_WINDOWPOS_CENTERED),
		get<int>("WINDOW_POS_Y", SDL_WINDOWPOS_CENTERED),
		get<int>("WINDOW_SIZE_X"),
		get<int>("WINDOW_SIZE_Y"),
		window_flags);
	check_sdl_error(window, "SDL_CreateWindow");
	push_cleanup_function(std::bind(SDL_DestroyWindow, window));

	// initializing GL context
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	push_cleanup_function(std::bind(SDL_GL_DeleteContext, gl_context));

	// initializing GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// creating the render context
	renderer = new Renderer(window);

	// create shader
	shader::create("test", "shader/vs.glsl", GL_VERTEX_SHADER);
	shader::create("test", "shader/fs.glsl", GL_FRAGMENT_SHADER);

	// create texture
	texture::create("orange", "media/dev.jpg");

	// test triangle
	RenderObject* test = create_render_object("test");
	std::vector<glm::vec3> pos = {
		glm::vec3(0.5, 0.5, 0),
		glm::vec3(-0.5, 0.5, 0),
		glm::vec3(0, -0.5, 0)
	};
	std::vector<glm::vec2> tc = {
		glm::vec2(2, 2),
		glm::vec2(-1, 2),
		glm::vec2(0.5, -1)
	};
	test->add_vertex_buffer("pos", pos, 0);
	test->add_vertex_buffer("tc", tc, 1);
	test->bind_texture("orange");
	renderer->register_render_object("test");


	// make the window visible
	SDL_ShowWindow(window);
}

void process_events() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				should_quit = true;
				break;
		}
	}
}

void loop() {
	process_events();
	renderer->render();
}


int main() {
	try {
		// init program
		init();

		// start the main loop
		while (!should_quit) {
			loop();
		}
	
	// print out errors and quit
	} catch (std::string str) {
		std::cerr << "[ERROR] " << str << std::endl;
		clean_up();
		return -1;
	}

	clean_up();
}