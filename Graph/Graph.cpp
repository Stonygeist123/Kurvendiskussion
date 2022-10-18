#include "Graph.hpp"

Graph::Graph(std::string function_s, std::string outdir, std::pair<float, std::map<float, float>> function)
	: function_s(function_s), outdir(outdir), function(function), term(function.first) {
	std::transform(function.second.begin(), function.second.end(), std::back_inserter(xs),
				   [](const std::pair<float, float>& p) { return p.first; });

	std::transform(function.second.begin(), function.second.end(), std::back_inserter(xf),
				   [](const std::pair<float, float>& p) { return p.second; });
}

std::pair<int, int> Graph::getScreenRange() {
	std::pair<int, int> range{};
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	range = { desktop.right, desktop.bottom };
	return range;
}

float Graph::calc_f(const float x) const {
	float y = 0;
	for (size_t i = 0; i < xs.size(); ++i) {
		const float exp = xs.at(i), fac = xf.at(i);
		const float add = fac * (exp == .5f ? std::sqrtf(x) : std::powf(x, exp));
		if (std::isnan(add))
			continue;
		y += add;
	}
	y += term * 10;
	return y;
}

std::string Graph::create_image() const {
	const std::string path = outdir + std::string("\\" + function_s + ".pgm");
	std::ofstream graph;
	graph.open(path);

	if (!graph.is_open()) {
		graph.clear();
		graph.open(path, std::ios::out);
		graph.close();
		graph.open(path);
	}

	std::stringstream ss{};
	std::vector<std::vector<bool>> img(screen_height, std::vector<bool>(screen_width, false));

	for (size_t h = 0; h < screen_height; ++h)
		for (size_t x = 0; x < screen_width; ++x) {
			float y_coordinate = -calc_f(x / x_factor + coordinate_min_x);
			long y = static_cast<long>((y_coordinate + y_offset) * y_factor);

			for (std::uint8_t i = 0; i < line_width; ++i)
				if (y + i < screen_height && x < screen_width && y > 0 && x >= 0 &&
					static_cast<long>(LONG_MAX + 1) != y)
					img.at(static_cast<size_t>(y - 1 + i)).at(x) = true;
		}

	for (size_t y = 0; y < screen_height; ++y) {
		for (size_t x = 0; x < screen_width; ++x)
			ss << (img.at(y).at(x)
					   ? (x == 0 ? "0" : " 0")
					   : ((screen_width / 2.f - line_width < x && x < screen_width / 2.f + line_width) ||
								  (screen_height / 2.f - line_width < y && y < screen_height / 2.f + line_width)
							  ? (x == 0 ? "6" : " 6")
							  : ((x == 0 ? "15" : " 15"))));
		if (y + 1 < screen_height)
			ss << '\n';
	}

	graph << "P2\n" << screen_width << ' ' << screen_height << "\n15\n" << ss.str();
	return path;
}
