#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace Utils {
	std::string readFile(const std::string& filepath) {
		std::string result;
		std::ifstream file(filepath, std::ios::in | std::ios::binary);
		if (file) {
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			if (size != -1) {
				result.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&result[0], size);
			} else {
				std::cout << "Could not read from file " << filepath << std::endl;
			}
		} else {
			std::cout << "Could not open file " << filepath << std::endl;
		}
		return result;
	}

	struct StringHelper {
		StringHelper(const std::string& s) : p(s.c_str()) {}
		operator const char** () { return &p; }
		const char* p;
	};


}