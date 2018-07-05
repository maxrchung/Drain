#include "BlankStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
BlankStroke::BlankStroke() {}
float BlankStroke::calculateLength() const {
	return 1 + thickness;
}
Vector2 BlankStroke::getEndPosition() const {
	return Vector2(0.5f, 0.0f);
}
Vector2 BlankStroke::getStartPosition() const {
	return Vector2(-0.5f, 0.0f);
}
void BlankStroke::createPoints(const Vector2& position, const float scale) {
}
void BlankStroke::createSprites(const Vector2& position, const float scale) {
}
void BlankStroke::draw(const Vector2& position,
					   const int startDraw,
					   const int endDraw,
					   const int startDrain,
					   const int endDrain,
					   const float scale) const {
}