#pragma once
#include <algorithm>
#include <fstream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <windows.graphics.h>
#include <wtypes.h>

constexpr float coordinate_max_x = 100, coordinate_min_x = -100, coordinate_max_y = 500, coordinate_min_y = -500,
				x_coordinate_range = coordinate_max_x - coordinate_min_x,
				y_coordinate_range = coordinate_max_y - coordinate_min_y, y_offset = -coordinate_min_y;
constexpr std::uint8_t line_width = 3;

class Graph {
public:
	std::vector<float> xs, xf;
	const float term;
	const std::string outdir, function_s;
	std::pair<float, std::map<float, float>> function;
	Graph(std::string, std::string, std::pair<float, std::map<float, float>>);

	static std::pair<int, int> getScreenRange();
	float calc_f(const float) const;
	std::string create_image() const;
};

const auto [screen_width, screen_height] = Graph::getScreenRange();
const float x_factor = screen_width / x_coordinate_range, y_factor = screen_height / y_coordinate_range;
