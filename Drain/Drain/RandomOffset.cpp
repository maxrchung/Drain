#include "RandomOffset.hpp"
#include <stdlib.h>
RandomOffset::RandomOffset(const int middle, const int variance)
	: middle{ middle }, variance{ variance } {
}
int RandomOffset::calculate(const int middle, const int variance) {
	const auto randomVariance = rand() % (variance + 1);
	const auto randomValue = middle + randomVariance;
	return randomValue;
}
int RandomOffset::calculate() {
	const auto randomValue = calculate(middle, variance);
	return randomValue;
}