#include "PointStroke.hpp"
PointStroke::PointStroke(const Vector2& start)
	: Stroke{ start, start } {
}
float PointStroke::calculateLength() const {
	return 0;
}
void PointStroke::createSprites(const Vector2& position, const float scale) {
}
void PointStroke::draw(const Vector2& position,
					   const int strokeStart,
					   const int strokeEnd,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) {
}