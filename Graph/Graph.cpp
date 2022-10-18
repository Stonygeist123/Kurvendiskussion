#include "Graph.hpp"

Graph::Graph(std::string outdir, std::vector<float> xf, std::vector<float> xs, float term)
	: outdir(outdir), xf(xf), xs(xs), term(term) {}

std::pair<int, int> Graph::getScreenRange() {
	std::pair<float, float> range{};
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
	const std::string path = outdir + std::string("/graph.pbm");
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
			float y_coordinate = calc_f(x / x_factor + coordinate_min_x);
			int y = (y_coordinate + y_offset) * y_factor;

			for (int i = y - line_width; i <= y + line_width; ++i)
				if (y < screen_height && x < screen_width && y - 1 >= 0 && x >= 0)
					img.at(static_cast<size_t>(y - 1)).at(x) = true;
		}

	for (size_t y = 0; y < screen_height; ++y) {
		for (size_t x = 0; x < screen_width; ++x)
			ss << (img.at(y).at(x) || (screen_width / 2.f - line_width < x && x < screen_width / 2.f + line_width) ||
						   (screen_height / 2.f - line_width < y && y < screen_height / 2.f + line_width)
					   ? (x == 0 ? "1 " : (x + 1 == screen_width ? " 1" : " 1 "))
					   : (x == 0 ? "0 " : (x + 1 == screen_width ? " 0" : " 0 ")));
		if (y + 1 < screen_height)
			ss << '\n';
	}

	graph << "P1\n" << screen_width << ' ' << screen_height << '\n' << ss.str();
	return path;
}
