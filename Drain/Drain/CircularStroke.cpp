#include "CircularStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CircularStroke::CircularStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: Stroke{ startPosition, endPosition }, center{ center } {
}
float CircularStroke::calculateLength() const {
	const auto startFromCenter = startPosition - center;
	const auto endFromCenter = endPosition - center;
	const auto angleBetween = startFromCenter.AngleBetween(endFromCenter);
	// Add thickness so PointStroke has length
	const auto length = fabsf(angleBetween) * endPosition.Magnitude() + thickness;
	return length;
}
void CircularStroke::createSprites(const Vector2& position, const float scale) {
	outer = Storyboard::CreateSprite(getPath(Path::Quarter), position + center * scale, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::Quarter), position + center * scale, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = position + endPosition.Normalize() * ((endPosition.Magnitude() + thickness * 0.5f) * scale);
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CircularStroke::draw(const Vector2& position,
						  const int startDraw,
						  const int endDraw,
						  const int startDrain,
						  const int endDrain,
						  const int endTime,
						  const int drawSpeed,
						  const Color& foreground,
						  const Color& background,
						  const float scale) const {
	outer->Color(startDraw, endDrain, foreground, foreground);
	inner->Color(startDraw, endDrain, background, background);
	horizontalCover->Color(startDraw, endDrain, background, background);
	verticalCover->Color(startDraw, endDrain, background, background);
	startPoint->Color(startDraw, startDraw, foreground, foreground);
	endPoint->Color(startDraw, startDraw, foreground, foreground);
	auto outerScale = (startPosition - center).Magnitude() * scale / imageSize + thickness * 0.5f * scale / imageSize;
	outer->Scale(startDraw, startDraw, outerScale, outerScale);
	auto innerScale = (startPosition - center).Magnitude() * scale / imageSize - thickness * 0.5f * scale / imageSize;
	inner->Scale(startDraw, startDraw, innerScale, innerScale);
	auto verticalCoverScale = outerScale * imageSize;
	auto horizontalCoverScale = innerScale * imageSize;
	const auto angleBetween = startPosition.AngleBetween(endPosition);
	// Set rotation and cover scale based on cw or ccw rotation
	float rotation;
	// CW
	if (angleBetween > 0) {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition);
		horizontalCover->ScaleVector(startDraw, endDraw, Vector2(0, horizontalCoverScale), Vector2(horizontalCoverScale, horizontalCoverScale), Easing::SineOut);
		verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, 0), Vector2(verticalCoverScale, verticalCoverScale), Easing::SineOut);
		horizontalCover->ScaleVector(startDrain, endDrain, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineOut);
		verticalCover->ScaleVector(startDrain, endDrain, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
	}
	// CCW
	else {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
		horizontalCover->ScaleVector(startDraw, endDraw, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
		verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
		horizontalCover->ScaleVector(startDrain, endDrain, Vector2(0, horizontalCoverScale), Vector2(horizontalCoverScale, horizontalCoverScale), Easing::SineOut);
		verticalCover->ScaleVector(startDrain, endDrain, Vector2(verticalCoverScale, 0), Vector2(verticalCoverScale, verticalCoverScale), Easing::SineIn);
	}
	outer->Rotate(startDraw, startDraw, rotation, rotation);
	inner->Rotate(startDraw, startDraw, rotation, rotation);
	horizontalCover->Rotate(startDraw, startDraw, rotation, rotation);
	verticalCover->Rotate(startDraw, startDraw, rotation, rotation);
	const auto thicknessScale = thickness * scale / imageSize;
	startPoint->Scale(startDraw - spawnTime, startDraw, 0, thicknessScale);
	startPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	endPoint->Scale(startDraw - spawnTime, startDraw, 0, thicknessScale);
	endPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	const auto endMove = position + endPosition * scale;
	const auto originalPosition = startPoint->position;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineIn);
		endPoint->MoveX(startDrain, endDrain, endMove.x, originalPosition.x, Easing::SineIn);
		endPoint->MoveY(startDrain, endDrain, endMove.y, originalPosition.y, Easing::SineOut);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineOut);
		endPoint->MoveX(startDrain, endDrain, endMove.x, originalPosition.x, Easing::SineOut);
		endPoint->MoveY(startDrain, endDrain, endMove.y, originalPosition.y, Easing::SineIn);
	}
	startPoint->Scale(endDrain, endDrain + spawnTime, thicknessScale, 0);
	endPoint->Scale(endDrain, endDrain + spawnTime, thicknessScale, 0);
}