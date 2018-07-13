#pragma once
#include "Color.hpp"
class SwatchTiming {
public:
	explicit SwatchTiming(const int startTime, const int endTime, const Color& startColor, const Color& endColor);
	bool contains(const int time) const;
	Color getColor(const int time) const;
	const int startTime;
	const int endTime;
private:
	const Color startColor;
	const Color endColor;
};