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
	Derivation(std::vector<float>, std::vector<float>, float);
	std::vector<std::string> get() const;
	std::pair<float, std::map<float, float>> getDeriv(std::vector<float>, std::vector<float>, float) const;
};
