#include "LineStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
LineStroke::LineStroke(const Vector2& startPosition, const Vector2& endPosition)
	: Stroke{ startPosition, endPosition } {
}
float LineStroke::calculateLength() const {
	// Add thickness so PointStroke has length
	const auto length = (endPosition - startPosition).Magnitude() + thickness;
	return length;
}
void LineStroke::createSprites(const Vector2& position, const float scale) {
	line = Storyboard::CreateSprite(getPath(Path::Square), position + startPosition * scale, Layer::Background, Origin::CentreLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void LineStroke::drain(const Vector2& position,
					   const int startStroke,
					   const int endStroke,
					   const int endTime,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) const {
	const auto length = (endPosition - startPosition).Magnitude();
	const auto thicknessScale = thickness * scale / imageSize;
	const auto startLineScaleVector = Vector2(0, thicknessScale);
	const auto endLineScaleVector = Vector2(length * scale / imageSize, thicknessScale);
	line->ScaleVector(startStroke, endStroke, endLineScaleVector, startLineScaleVector);
	startPoint->Scale(endStroke, endStroke + spawnTime, thicknessScale, 0);
	endPoint->Scale(endStroke, endStroke + spawnTime, thicknessScale, 0);
	endPoint->Move(startStroke, endStroke, endPoint->position, startPoint->position);
}
void LineStroke::draw(const Vector2& position,
					  const int startStroke,
					  const int endStroke,
					  const int endTime,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) const {
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition - startPosition);
	line->Rotate(startStroke, startStroke, rotation, rotation);
	const auto length = (endPosition - startPosition).Magnitude();
	const auto thicknessScale = thickness * scale / imageSize;
	const auto startLineScaleVector = Vector2(0, thicknessScale);
	const auto endLineScaleVector = Vector2(length * scale / imageSize, thicknessScale);
	line->ScaleVector(startStroke, endStroke, startLineScaleVector, endLineScaleVector);
	startPoint->Scale(startStroke - spawnTime, startStroke, 0, thicknessScale);
	startPoint->Scale(startStroke, startStroke, thicknessScale, thicknessScale);
	endPoint->Scale(startStroke - spawnTime, startStroke, 0, thicknessScale);
	endPoint->Scale(startStroke, startStroke, thicknessScale, thicknessScale);
	endPoint->Move(startStroke, endStroke, startPoint->position, position + endPosition * scale);
}