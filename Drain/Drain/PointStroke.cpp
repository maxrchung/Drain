#include "PointStroke.hpp"
PointStroke::PointStroke(const Vector2& startPosition)
	: startPosition{ startPosition } {
}
float PointStroke::calculateLength() const {
	// Add thickness so PointStroke has length
	return thickness;
}
Vector2 PointStroke::getEndPosition() const {
	return startPosition;
}
Vector2 PointStroke::getStartPosition() const {
	return startPosition;
}
void PointStroke::createPoints(const Vector2& position, const float scale) {
}
void PointStroke::createSprites(const Vector2& position, const float scale) {
}
void PointStroke::draw(const Vector2& position,
					   const int startDraw,
					   const int endDraw,
					   const int startDrain,
					   const int endDrain,
					   const float scale) const {
}