#pragma once

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS 1
#include <glm/glm.hpp>


#include <iostream>
#include <sstream>
#include <functional>

void push_cleanup_function(std::function<void()> f);
void clean_up();

void check_sdl_error(void* object, const std::string& func_name);
void check_sdl_error(int error_code, const std::string& func_name);