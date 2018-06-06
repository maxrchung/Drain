#include "CircularStroke.hpp"
CircularStroke::CircularStroke(const Vector2& start, const Vector2& end, const Vector2& center)
	: Stroke{ start, end }, center{ center } {
}
float CircularStroke::calculateLength() const {
	const auto startFromCenter = start - center;
	const auto endFromCenter = end - center;
	const auto angleBetween = startFromCenter.AngleBetween(endFromCenter);
	const auto length = angleBetween * end.Magnitude();
	return length;
}