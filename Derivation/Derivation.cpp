#include "Derivation.hpp"

Derivation::Derivation(std::pair<float, std::map<float, float>> function) : function(function), term(function.first) {
	std::transform(function.second.begin(), function.second.end(), std::back_inserter(xs),
				   [](const std::pair<float, float>& p) { return p.first; });

	std::transform(function.second.begin(), function.second.end(), std::back_inserter(xf),
				   [](const std::pair<float, float>& p) { return p.second; });
}

std::vector<std::string> Derivation::get() const {
	float currentTerm = 0;
	std::vector<std::string> deris{};
	if (xs.empty())
		return { "f(x) = 0" };
	else {
		std::optional<std::pair<float, std::vector<std::pair<float, float>>>> curDeriv = std::nullopt;
		for (unsigned short i = 0; i < 3; ++i) {
			std::pair<float, std::vector<std::pair<float, float>>> deriv;
			if (curDeriv.has_value() && !curDeriv.value().second.empty()) {
				std::vector<float> curXf{}, curXs{};
				for (const auto& [exp, fac] : curDeriv.value().second) {
					curXs.push_back(exp);
					curXf.push_back(fac);
				}
				deriv = getDeriv(curXf, curXs, curDeriv.value().first);
			}
			else if (!curDeriv.has_value())
				deriv = getDeriv(xf, xs, term);
			else
				break;

			std::sort(deriv.second.begin(), deriv.second.end(),
					  [](const std::pair<float, float>& p1, const std::pair<float, float>& p2) {
						  return p1.first > p2.first;
					  });

			std::string derivS = "";
			for (size_t i = 0; i < deriv.second.size(); ++i) {
				auto it = deriv.second.begin();
				std::advance(it, i);
				const auto& [exp, fac] = *it;
				if (i + 1 < deriv.second.size())
					std::advance(it, 1);

				derivS += std::to_string(std::abs(fac)) + "x" + (exp == 1 ? "" : "^" + std::to_string(exp)) +
						  (i + 1 < deriv.second.size() ? (std::abs(it->second) == it->second ? " + " : " - ") : "");
			}

			if (deriv.first != 0)
				derivS += (deriv.second.empty() ? "" : (std::abs(deriv.first) == deriv.first ? " + " : " - ")) +
						  std::to_string(std::abs(deriv.first));

			deris.push_back("\u001b[31mf(x) = " + derivS + "\u001b[0m");
			curDeriv = deriv;
		}
	}

	return deris;
}

std::pair<float, std::vector<std::pair<float, float>>> Derivation::getDeriv(std::vector<float> xf,
																			std::vector<float> xs, float term) const {
	std::pair<float, std::vector<std::pair<float, float>>> result{};
	if (xs.empty())
		return { 0.f, {} };

	if (const auto it = std::find(xs.begin(), xs.end(), 1); it != xs.end()) {
		const size_t d = std::distance(xs.begin(), it);
		const float fac = xf.at(d);
		xs.erase(it);
		xf.erase(std::next(xf.begin(), d));
		result = { fac, {} };
	}

	if (xs.size() > 0) {
		size_t i = 0;
		std::for_each(xs.begin(), xs.end(), [&xf, &i, &result](const float& f) {
			result.second.push_back({ f - 1, xf.at(i) * f });
			++i;
		});
	}

	return result;
}
