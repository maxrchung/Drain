#include "CircularStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
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
void CircularStroke::createSprites(const Vector2& position, const float scale) {
}
void CircularStroke::draw(const Vector2& position,
						  const int strokeStart,
						  const int strokeEnd,
						  const int drawSpeed,
						  const Color& foreground,
						  const Color& background,
						  const float scale) {
}