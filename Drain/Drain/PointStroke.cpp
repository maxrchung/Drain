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
					   const int startStroke,
					   const int endStroke,
					   const int endTime,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) {
}