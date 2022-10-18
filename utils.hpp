#pragma once
#include <sstream>
#include <string>
#include <vector>

inline void split(const std::string& str, const char delim, std::vector<std::string>& result) {
	std::stringstream ss(str);
	std::string s;
	while (std::getline(ss, s, delim))
		result.push_back(s);
}

inline std::vector<std::string> split(std::string str, const char delim) {
	std::vector<std::string> result;
	size_t pos = 0;
	while ((pos = str.find(delim)) != std::string::npos) {
		result.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	result.push_back(str);

	return result;
}

inline float format(const float& f) {
	if (f == -0)
		return 0;
	return std::lround(f) == f ? (long)f : f;
}