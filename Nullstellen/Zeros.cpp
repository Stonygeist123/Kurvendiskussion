#include "Zeros.hpp"

Zeros::Zeros(std::vector<float> xf, std::vector<float> xs, float term) : xf(xf), xs(xs), term(term) {}

std::optional<std::vector<float>> Zeros::get() const {
	if (xs.size() == 0)
		return term == 0 ? std::make_optional(std::vector<float>{ 0 }) : std::nullopt;

	const float& xmax = *std::max_element(xs.begin(), xs.end());
	if (xmax == 1)
		return std::vector{ -term };
	else if (xmax == 2) {
		if (xs.size() == 2) {
			std::vector<float> newXf{};
			std::transform(xf.cbegin(), xf.cend(), std::back_inserter(newXf),
						   [&](const float& f) { return f / xf.at(0); });

			const float newTerm = term / xf.at(0);
			const float p2 = newXf.at(1) / 2;
			const float rad = p2 * p2 - newTerm;
			if (std::abs(rad) != rad)
				return std::nullopt;
			const float sq = std::sqrtf(rad);
			return std::vector{ -p2 + sq, -p2 - sq };
		}
		else {
			float n = -term / xf[0];
			if (std::abs(n) != n)
				return std::nullopt;

			n = std::sqrtf(n);
			return std::vector{ -n, n };
		}
	}
	else {
		if (xs.size() == 1) {
			if (xmax == 3) {
				float n = -term / xf[0];
				n = std::cbrtf(n);
				return std::vector{ n };
			}

			float n = -term;
			n /= xf[0];
			const std::string expS = std::to_string(xs[0]), expSub = expS.substr(expS.find('.') + 1);
			const bool isInt = std::all_of(expSub.begin(), expSub.end(), [](const char& c) { return c == '0'; });
			if (std::abs(n) != n && (isInt && std::lround(xs[0]) % 2 == 0))
				return std::nullopt;

			n = std::pow(n, 1.f / xs[0]);
			return isInt && std::lround(xs[0]) % 2 == 0 ? std::vector{ -n, n } : std::vector{ n };
		}
	}
}