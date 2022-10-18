#pragma once
#include <algorithm>
#include <cmath>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

class Zeros {
public:
	std::vector<float> xs, xf;
	float term;
	Zeros(std::vector<float>, std::vector<float>, float);
	std::optional<std::vector<float>> get() const;
};