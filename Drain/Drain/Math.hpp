#pragma once
// Utility class for some math calculations
struct Math {
	static constexpr float pi = 3.14159f;
	static const float sqrt2;
	static float degreesToRadians(const float degrees);
	static float radiansToDegrees(const float radians);
};