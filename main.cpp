#include "Derivation/Derivation.hpp"
#include "Graph/Graph.hpp"
#include "Zeros/Zeros.hpp"
#include "utils.hpp"
#include <iostream>
#include <numbers>
#include <regex>
#include <set>
#include <thread>

int main() {
	std::string input;
	while (input != "stop") {
		input = "";
		std::cout << "Gebe eine Funktion ein:\n\u001b[32m> ";
		std::getline(std::cin, input);
		if (input.empty())
			continue;
		std::cout << "\u001b[0m";

		if (input.contains("pi"))
			input.replace(input.find("pi"), 2, "3.1415927");
		if (input.contains("e"))
			input.replace(input.find('e'), 1, "2.7182817");

		std::pair<float, std::map<float, float>> function = generate_func(input);

		const Zeros zeros = Zeros(function);
		std::thread t1{ [&zeros] {
			const std::optional<std::vector<float>> z = zeros.get();
			if (z.has_value() && !z.value().empty()) {
				std::set<float> zS = std::set(z.value().begin(), z.value().end());
				for (unsigned long i = 0; i < zS.size(); ++i)
					std::cout << "Nullstelle " << i + 1 << ": \u001b[36m("
							  << format(std::vector(zS.begin(), zS.end()).at(i)) << " | " << 0 << ")\u001b[0m\n\n";
			}
			else
				std::cout << "Keine Nullstelle\n\n";
		} };
		t1.join();

		const Derivation derivation = Derivation(function);
		std::thread t2{ [&derivation] {
			const std::vector<std::string> derivs = derivation.get();

			for (size_t i = 0; i < derivs.size(); ++i)
				std::cout << "Ableitung " << i + 1 << ": " << derivs.at(i) << '\n';
			std::cout << '\n';
		} };
		t2.join();

		const Graph graph = Graph(input, "C:\\Users\\Yunus\\source\\repos\\Kurvendiskussion", function);
		std::thread t3{ [&graph] { std::cout << graph.create_image() << "\n\n"; } };
		t3.join();
	}
}
