#include "texture.hpp"

#include "common.hpp"
#include <SDL2/SDL_image.h>
#include <map>


std::map<std::string, SDL_Surface*> texmap;

void texture::init() {
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	push_cleanup_function(IMG_Quit);
}

void texture::create(const std::string& name, const std::string& filename) {
	SDL_Surface* img = IMG_Load(filename.c_str());
	if (img) {
		texmap.emplace(name, img);
	}
}

void texture::remove(const std::string& name) {
	auto it = texmap.find(name);
	if (it != texmap.end()) {
		SDL_FreeSurface(it->second);
		texmap.erase(it);
		std::cout << "yeah" << std::endl;
	}
}

void texture::remove_all() {
	for (auto& p : texmap) {
		SDL_FreeSurface(p.second);
	}
	texmap.clear();
}