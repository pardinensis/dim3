#pragma once

#include "common.hpp"


namespace texture {
	void init();

	void create(const std::string& name, const std::string& filename, SDL_Renderer* renderer);
	void remove(const std::string& name);
	void remove_all();

	SDL_Texture* get(const std::string& name);
}