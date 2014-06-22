#include "fileutils.hpp"

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

std::map<std::string, std::string> config_map;

void parse_config_file(const std::string& filename) {
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	if (!fs.is_open()) {
		throw "could not open file: " + filename;
	}

	std::string line, key, value;
	while (std::getline(fs, line)) {
		auto begin = line.find_first_not_of(" \f\t\v");
		if (begin == std::string::npos) continue;

		// skip commentaries beginning with #
		if (line[begin] == '#') continue;

		// extract key 
		auto end = line.find_first_of(" \f\t\v", begin);
		if (end == std::string::npos) continue;
		key = line.substr(begin, end);

		// extract value
		begin = line.find_first_not_of(" \f\t\v", end+1);
		end = line.find_last_not_of(" \f\t\v") + 1;
		value = line.substr(begin, end - begin);

		// store key-value pair
		config_map[key] = value;
	}
}

template <typename T>
T get(const std::string& key) {
	auto elem = config_map.find(key);
	if (elem == config_map.end()) {
		std::stringstream ss;
		ss << "could not find config key: " << key;
		throw ss.str();
	}

	std::stringstream ss;
	ss << elem->second;
	T val;
	ss >> val;
	return val;
}
template std::string get<std::string>(const std::string& key);
template int get<int>(const std::string& key);
