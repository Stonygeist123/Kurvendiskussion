#include "Derivation/Derivation.hpp"
#include "Graph/Graph.hpp"
#include "Nullstellen/Zeros.hpp"
#include "utils.hpp"
#include <iostream>
#include <regex>
#include <set>

int main() {
	std::string func;
	while (func != "stop") {
		func = "";
		std::cout << "Gebe eine Funktion ein:\n\u001b[32m> ";
		std::getline(std::cin, func);
		if (func.empty())
			continue;
		std::cout << "\u001b[0m";

		std::vector<float> xs{}, xf{};
		float term = 0;
		bool neg = false;

		const auto x = split(func, ' ');
		for (const std::string& f : split(func, ' ')) {
			float exponent = 1;
			if (f.contains('x')) {
				if (f.contains(('^')))
					exponent = std::stof(f.substr(std::distance(f.begin(), std::find(f.begin(), f.end(), '^')) + 1));

				xs.push_back(exponent);
				xf.push_back(std::isdigit(f.at(0))
								 ? std::stof(f.substr(0, std::distance(f.begin(), std::find(f.begin(), f.end(), 'x'))))
								 : 1);
				xf.at(xf.size() - 1) = -xf.at(xf.size() - 1);
			}
			else if (f == "-") {
				neg = true;
				continue;
			}
			else if (f.end() != std::find_if(f.begin(), f.end(), [](const unsigned char& c) {
						 return !isdigit(c) && c != '.' && c != '-';
					 }))
				continue;
			else {
				const float t = std::stof(f);
				term = neg ? -t : t;
			}

			neg = false;
		}

		const Zeros zeros = Zeros(xf, xs, term);
		const std::optional<std::vector<float>> z = zeros.get();
		if (z.has_value() && !z.value().empty()) {
			std::set<float> zS = std::set(z.value().begin(), z.value().end());
			for (unsigned long i = 0; i < zS.size(); ++i)
				std::cout << "Nullstelle " << i + 1 << ": \u001b[36m("
						  << format(std::vector(zS.begin(), zS.end()).at(i)) << " | " << 0 << ")\u001b[0m\n\n";
		}
		else
			std::cout << "Keine Nullstelle\n\n";

		/*const Derivation derivation = Derivation(xf, xs, term);
		const std::vector<std::string> derivs = derivation.get();

		for (size_t i = 0; i < derivs.size(); ++i)
			std::cout << "Ableitung " << i + 1 << ": " << derivs.at(i) << '\n';
		std::cout << '\n'; */

		const Graph graph = Graph("C:\\Users\\Yunus\\source\\repos\\Kurvendiskussion", xf, xs, term);
		graph.create_image();
	}
}
