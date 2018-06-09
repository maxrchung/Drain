#include "CircularStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CircularStroke::CircularStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: Stroke{ startPosition, endPosition }, center{ center } {
}
float CircularStroke::calculateLength() const {
	const auto startFromCenter = startPosition - center;
	const auto endFromCenter = endPosition - center;
	const auto angleBetween = startFromCenter.AngleBetween(endFromCenter);
	// Always add thickness so PointStroke can have draw time
	const auto length = angleBetween * endPosition.Magnitude() + thickness;
	return length;
}
void CircularStroke::draw(const Vector2& position,
						  const int startStroke,
						  const int endStroke,
						  const int drawSpeed,
						  const Color& foreground,
						  const Color& background,
						  const float scale) {
}