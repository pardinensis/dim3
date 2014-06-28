#pragma once

#include "common.hpp"

namespace texture {
	void init();

	void create(const std::string& name, const std::string& filename);
	void remove(const std::string& name);
	void remove_all();
}