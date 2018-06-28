#include "RandomRange.hpp"
#include <stdlib.h>
RandomRange::RandomRange(const int start, const int end)
	: start{ start }, end{ end } {
}
int RandomRange::calculate(const int start, const int end) {
	const auto total = end - start;
	const auto variance = rand() % (total + 1);
	const auto value = start + variance;
	return value;
}
int RandomRange::calculate() {
	const auto value = calculate(start, end);
	return value;
}