#include "texture.hpp"

#include "common.hpp"

#include <SDL2/SDL_image.h>
#include <map>
#include <functional>


std::map<std::string, GLuint> texmap;


void texture::init() {
	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
		push_cleanup_function(remove_all);
		push_cleanup_function(IMG_Quit);
	}
}

void texture::create(const std::string& name, const std::string& filename) {
	if (texmap.find(name) != texmap.end()) {
		return;
	}
	
	SDL_Surface* img = IMG_Load(filename.c_str());
	check_sdl_error(img, std::string("IMG_Load(") + filename);

	GLuint tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(img);

	texmap.emplace(name, tex_id);
}

void texture::remove(const std::string& name) {
	auto it = texmap.find(name);
	if (it != texmap.end()) {
		glDeleteTextures(1, &it->second);
		texmap.erase(it);
	}
}

void texture::remove_all() {
	for (auto& p : texmap) {
		glDeleteTextures(1, &p.second);
	}
	texmap.clear();
}


GLuint texture::get(const std::string& name) {
	auto it = texmap.find(name);
	if (it != texmap.end()) {
		return it->second;
	} else {
		std::stringstream ss;
		ss << "could not find texture " << name;
		throw ss.str();
	}
}