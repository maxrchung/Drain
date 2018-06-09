#include "LineStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
LineStroke::LineStroke(const Vector2& startPosition, const Vector2& endPosition)
	: Stroke{ startPosition, endPosition } {
}
float LineStroke::calculateLength() const {
	// Always add thickness so PointStroke can have draw time
	const auto length = (endPosition - startPosition).Magnitude() + thickness;
	return length;
}
void LineStroke::draw(const Vector2& position,
					  const int startStroke,
					  const int endStroke,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) {
	auto const line = Storyboard::CreateSprite(getPath(Path::Square), position + startPosition * scale, Layer::Background, Origin::CentreLeft);
	auto const startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	auto const endPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + endPosition * scale, Layer::Background);
}