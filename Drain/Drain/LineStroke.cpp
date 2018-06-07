#include "LineStroke.hpp"
LineStroke::LineStroke(const Vector2& start, const Vector2& end) 
	: Stroke{ start, end } {
}
float LineStroke::calculateLength() const {
	const auto length = (end - start).Magnitude();
	return length;
}
float LineStroke::createSprites() {
}
void LineStroke::draw(const Vector2& position, const CharacterConfig& config) {
}