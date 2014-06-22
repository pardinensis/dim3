#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <functional>

#include "fileutils.hpp"


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool should_quit = false;


std::stack<std::function<void()>> clean_up_stack;

void init() {
	parse_config_file("config.txt");

	// initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::stringstream ss;
		ss << "sdl_init failed: " << SDL_GetError();
		throw ss.str();
	}
	clean_up_stack.push(SDL_Quit);

	// creating a window
	window = SDL_CreateWindow(
		get<std::string>("WINDOW_NAME").c_str(),
		get<int>("WINDOW_POS_X"),
		get<int>("WINDOW_POS_Y"),
		get<int>("WINDOW_SIZE_X"),
		get<int>("WINDOW_SIZE_Y"),
		SDL_WINDOW_SHOWN);
	if (!window) {
		std::stringstream ss;
		ss << "sdl_create_window failed: " << SDL_GetError();
		throw ss.str();
	}
	clean_up_stack.push(std::bind(SDL_DestroyWindow, window));

	// creating the render context
	renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::stringstream ss;
		ss << "sdl_create_renderer failed: " << SDL_GetError();
		throw ss.str();
	}
	clean_up_stack.push(std::bind(SDL_DestroyRenderer, renderer));

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
	while (!should_quit) {
		process_events();
	}
}

void clean_up() {
	while (!clean_up_stack.empty()) {
		clean_up_stack.top()();
		clean_up_stack.pop();
	}
}

int main() {
	try {
		init();
		loop();
	} catch (std::string str) {
		std::cerr << "[ERROR] " << str << std::endl;
		clean_up();
		return -1;
	}

	clean_up();
}