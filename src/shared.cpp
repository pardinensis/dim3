#include "shared.hpp"

#include <stack>

std::stack<std::function<void()>> clean_up_stack;

void push_cleanup_function(std::function<void()> f) {
	clean_up_stack.push(f);
}

void clean_up() {
	while (!clean_up_stack.empty()) {
		clean_up_stack.top()();
		clean_up_stack.pop();
	}
}

void check_sdl_error(void* object, const std::string& func_name) {
	if (!object) {
		std::stringstream ss;
		ss << func_name << " failed: " << SDL_GetError();
		throw ss.str();
	}
}

void check_sdl_error(int error_code, const std::string& func_name) {
	if (error_code != 0) {
		std::stringstream ss;
		ss << func_name << " failed: " << SDL_GetError();
		throw ss.str();
	}
}