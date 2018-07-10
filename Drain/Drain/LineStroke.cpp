#include "LineStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
LineStroke::LineStroke(const Vector2& startPosition, const Vector2& endPosition)
	: startPosition{ startPosition }, endPosition{ endPosition } {
}
float LineStroke::calculateLength() const {
	// Add thickness so PointStroke has length
	const auto length = (endPosition - startPosition).Magnitude() + thickness;
	return length;
}
Vector2 LineStroke::getEndPosition() const {
	return endPosition;
}
Vector2 LineStroke::getStartPosition() const {
	return startPosition;
}
void LineStroke::createPoints(const Vector2& position, const float scale) {
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void LineStroke::createSprites(const Vector2& position, const float scale) {
	line = Storyboard::CreateSprite(getPath(Path::Square), position + startPosition * scale, Layer::Background, Origin::CentreLeft);
}
void LineStroke::draw(const Vector2& position,
					  const int startDraw,
					  const int endDraw,
					  const int startDrain,
					  const int endDrain,
					  const float scale) const {
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition - startPosition);
	line->Rotate(startDraw, startDraw, rotation, rotation);
	const auto length = (endPosition - startPosition).Magnitude();
	const auto thicknessScale = thickness * scale / imageSize;
	const auto startLineScaleVector = Vector2(0, thicknessScale);
	const auto endLineScaleVector = Vector2(length * scale / imageSize, thicknessScale);
	line->ScaleVector(startDraw, endDraw, startLineScaleVector, endLineScaleVector);
	endPoint->Move(startDraw, endDraw, startPoint->position, position + endPosition * scale);
	scalePoints({ startPoint, endPoint }, startDraw, scale);
	fadeSprites({ line }, startDrain, endDrain);
	fadePoints({ startPoint, endPoint }, startDrain, endDrain);
}