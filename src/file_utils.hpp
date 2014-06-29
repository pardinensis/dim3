#pragma once

#include <string>

void parse_config_file(const std::string& filename);

template<typename T> T get(const std::string& key);
template<typename T> T get(const std::string& key, T default_value);