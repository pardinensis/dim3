#include "fileutils.hpp"
#include "renderer.hpp"
#include "texture.hpp"
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

	// creating the render context
	renderer = new Renderer(window);

	// initializing SDL_image
	texture::init();


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