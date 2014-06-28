#pragma once

#include <SDL2/SDL.h>


#include <iostream>
#include <sstream>
#include <functional>

void push_cleanup_function(std::function<void()> f);
void clean_up();

void check_sdl_error(void* object, const std::string& func_name);
void check_sdl_error(int error_code, const std::string& func_name);