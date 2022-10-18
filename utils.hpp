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

inline std::pair<float, std::map<float, float>> generate_func(std::string func) {
	std::pair<float, std::map<float, float>> result{ 0, {} };
	bool neg = false;

	const auto x = split(func, ' ');
	for (const std::string& f : split(func, ' ')) {
		float exp = 1;
		if (f.contains('x')) {
			if (f.contains(('^')))
				exp = std::stof(f.substr(std::distance(f.begin(), std::find(f.begin(), f.end(), '^')) + 1));

			result.second.insert(
				{ exp, std::isdigit(f.at(0))
						   ? std::stof(f.substr(0, std::distance(f.begin(), std::find(f.begin(), f.end(), 'x'))))
						   : 1 });

			if (neg)
				result.second.at(exp) = -result.second.at(exp);
		}
		else if (f == "-") {
			neg = true;
			continue;
		}
		else if (f.end() != std::find_if(f.begin(), f.end(),
										 [](const unsigned char& c) { return !isdigit(c) && c != '.' && c != '-'; }))
			continue;
		else
			result.first = neg ? -std::stof(f) : std::stof(f);
		neg = false;
	}

	return result;
}
