#include "PointStroke.hpp"
PointStroke::PointStroke(const Vector2& start)
	: Stroke{ start, start } {
}
float PointStroke::calculateLength() const {
	return 0;
}
void PointStroke::createSprites() {
}
void PointStroke::draw(const Vector2& position, const CharacterConfig& config) {
}