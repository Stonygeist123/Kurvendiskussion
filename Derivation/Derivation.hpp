#pragma once
#include <algorithm>
#include <array>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

class Derivation {
public:
	std::vector<float> xs, xf;
	float term;
	std::pair<float, std::map<float, float>> function;
	Derivation(std::pair<float, std::map<float, float>>);
	std::vector<std::string> get() const;
	std::pair<float, std::vector<std::pair<float, float>>> getDeriv(std::vector<float>, std::vector<float>,
																	float) const;
};
