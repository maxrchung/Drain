#include "RandomRange.hpp"
#include <stdlib.h>
RandomRange::RandomRange(const int start, const int end, const float divisor)
	: start{ start }, end{ end }, divisor{ divisor } {
}
float RandomRange::calculate(const int start, const int end, const float divisor) {
	const auto total = end - start;
	const auto variance = rand() % (total + 1);
	const auto value = start + variance;
	const auto divided = value / divisor;
	return divided;
}
float RandomRange::calculate() const {
	const auto value = calculate(start, end, divisor);
	return value;
}