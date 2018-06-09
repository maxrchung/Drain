#include "PointStroke.hpp"
PointStroke::PointStroke(const Vector2& startPosition)
	: Stroke{ startPosition, startPosition } {
}
float PointStroke::calculateLength() const {
	// Always add thickness so PointStroke can have draw time
	return thickness;
}
void PointStroke::draw(const Vector2& position,
					   const int startStroke,
					   const int endStroke,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) {
}