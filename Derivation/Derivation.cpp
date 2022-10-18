#include "Derivation.hpp"

Derivation::Derivation(std::vector<float> xf, std::vector<float> xs, float term) : xf(xf), xs(xs), term(term) {}

std::vector<std::string> Derivation::get() const {
	float currentTerm = 0;
	std::vector<std::string> deris{};
	if (xs.empty())
		return { "f(x) = 0" };
	else {
		std::optional<std::pair<float, std::map<float, float>>> curDeriv = std::nullopt;
		for (unsigned short i = 0; i < 3; ++i) {
			std::pair<float, std::map<float, float>> deriv;
			if (curDeriv.has_value() && !curDeriv.value().second.empty()) {
				std::vector<float> curXf{}, curXs{};
				for (const auto& [fac, exp] : curDeriv.value().second) {
					curXf.push_back(fac);
					curXs.push_back(exp);
				}
				deriv = getDeriv(curXf, curXs, curDeriv.value().first);
			}
			else if (!curDeriv.has_value())
				deriv = getDeriv(xf, xs, term);
			else
				break;

			std::string derivS = "";
			for (size_t i = 0; i < deriv.second.size(); ++i) {
				auto it = deriv.second.rbegin();
				std::advance(it, i);
				const auto& [fac, exp] = *it;
				if (i + 1 < deriv.second.size())
					std::advance(it, 1);

				derivS += std::to_string(fac) + "x" + (exp == 1 ? "" : "^" + std::to_string(exp)) +
						  (i + 1 < deriv.second.size() ? (std::abs(it->first) == it->first ? " + " : " - ") : "");
			}
			if (deriv.first != 0)
				derivS += (deriv.second.empty() ? "" : (std::abs(deriv.first) == deriv.first ? " + " : " - ")) +
						  std::to_string(deriv.first);

			if (derivS.contains('.'))
				for (auto it = std::find(derivS.begin(), derivS.end(), '.'); it != derivS.end();
					 it = std::find(derivS.begin(), derivS.end(), '.')) {
					size_t count = derivS.find('.') - 1;
					const auto x = *it;

					while (++count + 1 < derivS.size()) {
						const auto c = derivS.at(count), d = derivS.at(count + 1);
						if ((std::isdigit(derivS.at(count + 1)) && derivS.at(count + 1) != '0') ||
							!std::isdigit(derivS.at(count + 1))) {
							count = 0;
							break;
						}
					}

					if (count != 0)
						derivS.erase(it, std::next(it, count));
				}

			deris.push_back("\u001b[31mf(x) = " + derivS + "\u001b[0m");
			curDeriv = deriv;
		}
	}

	return deris;
}

std::pair<float, std::map<float, float>> Derivation::getDeriv(std::vector<float> xf, std::vector<float> xs,
															  float term) const {
	std::pair<float, std::map<float, float>> result{};
	if (xs.empty())
		return { 0, {} };

	if (const auto it = std::find(xs.begin(), xs.end(), 1); it != xs.end()) {
		const float t = xf.at(std::distance(xs.begin(), it));
		xs.erase(it);
		result = { t, {} };
	}

	if (xs.size() > 0) {
		size_t i = 0;
		std::for_each(xs.begin(), xs.end(), [&xf, &i, &result](const float& f) {
			result.second.insert({ xf.at(i) * f, f - 1 });
			++i;
		});
	}

	return result;
}
