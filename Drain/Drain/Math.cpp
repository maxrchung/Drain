#include <math.h>
#include "Math.hpp"
const float Math::sqrt2 = sqrtf(2);
float Math::degreesToRadians(const float degrees) {
	const auto radians = degrees * 180.0f / pi;
		return radians;
}
float Math::radiansToDegrees(const float radians) {
	const auto degrees = radians * pi / 180.0f;
	return degrees;
}