#include "SwatchTiming.hpp"

SwatchTiming::SwatchTiming(const int startTime, const int endTime, const Color& startColor, const Color& endColor)
	: startTime{ startTime }, endTime{ endTime }, startColor{ startColor }, endColor{ endColor } {
}
bool SwatchTiming::contains(const int time) const {
	const auto contained = time >= startTime && time <= endTime;
	return contained;
}
Color SwatchTiming::getColor(const int time) const {
	const auto relativeTime = time - startTime;
	const auto relativeEnd = endTime - startTime;
	const auto timeFraction = static_cast<float>(relativeTime) / relativeEnd;
	const auto relativeColor = endColor - startColor;
	const auto colorFraction = relativeColor * timeFraction;
	const auto color = startColor + colorFraction;
	return color;
}