#pragma once
#include <algorithm>
#include <cmath>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

class Zeros {
public:
	std::vector<float> xs, xf;
	float term;
	std::pair<float, std::map<float, float>> function;
	Zeros(std::pair<float, std::map<float, float>>);
	std::optional<std::vector<float>> get() const;
};
