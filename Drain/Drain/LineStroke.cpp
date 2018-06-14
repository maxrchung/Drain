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
void LineStroke::draw(const Vector2& position,
					  const int startDraw,
					  const int endDraw,
					  const int startDrain,
					  const int endDrain,
					  const int endTime,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) const {
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition - startPosition);
	line->Rotate(startDraw, startDraw, rotation, rotation);
	const auto length = (endPosition - startPosition).Magnitude();
	const auto thicknessScale = thickness * scale / imageSize;
	const auto startLineScaleVector = Vector2(0, thicknessScale);
	const auto endLineScaleVector = Vector2(length * scale / imageSize, thicknessScale);
	line->ScaleVector(startDraw, endDraw, startLineScaleVector, endLineScaleVector);
	startPoint->Scale(startDraw - spawnTime, startDraw, 0, thicknessScale);
	startPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	endPoint->Scale(startDraw - spawnTime, startDraw, 0, thicknessScale);
	endPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	endPoint->Move(startDraw, endDraw, startPoint->position, position + endPosition * scale);
	line->ScaleVector(startDrain, endDrain, endLineScaleVector, startLineScaleVector);
	startPoint->Scale(endDrain, endDrain + spawnTime, thicknessScale, 0);
	endPoint->Scale(endDrain, endDrain + spawnTime, thicknessScale, 0);
	endPoint->Move(startDrain, endDrain, endPoint->position, startPoint->position);
}