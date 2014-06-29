#include "texture.hpp"

#include "common.hpp"

#include <SDL2/SDL_image.h>
#include <map>
#include <functional>


std::map<std::string, SDL_Texture*> texmap;


void texture::init() {
	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
		push_cleanup_function(remove_all);
		push_cleanup_function(IMG_Quit);
	}
}

void texture::create(const std::string& name, const std::string& filename, SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(filename.c_str());
	check_sdl_error(img, std::string("IMG_Load(") + filename);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, img);
	check_sdl_error(tex, "SDL_CreateTextureFromSurface");

	SDL_FreeSurface(img);

	texmap.emplace(name, tex);
}

void texture::remove(const std::string& name) {
	auto it = texmap.find(name);
	if (it != texmap.end()) {
		SDL_DestroyTexture(it->second);
		texmap.erase(it);
	}
}

void texture::remove_all() {
	for (auto& p : texmap) {
		SDL_DestroyTexture(p.second);
	}
	texmap.clear();
}


SDL_Texture* get(const std::string& name) {
	auto it = texmap.find(name);
	if (it != texmap.end()) {
		return it->second;
	}
	return nullptr;
}