#include "PointStroke.hpp"
PointStroke::PointStroke(const Vector2& startPosition)
	: Stroke{ startPosition, startPosition } {
}
float PointStroke::calculateLength() const {
	// Add thickness so PointStroke has length
	return thickness;
}
void PointStroke::createSprites(const Vector2& position, const float scale) {

}
void PointStroke::draw(const Vector2& position,
					   const int startDraw,
					   const int endDraw,
					   const int startDrain,
					   const int endDrain,
					   const Color& background,
					   const Color& foreground,
					   const float scale) const {
}