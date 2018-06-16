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
bool CircularStroke::isClockwiseRotation() const {
	const auto angleBetween = startPosition.AngleBetween(endPosition);
	const auto isClockwise = angleBetween > 0;
	return isClockwise;
}
void CircularStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::Quarter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::Quarter), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = endPosition.Normalize() * (endPosition.Magnitude() + thickness * 0.5f) * scale;
	Origin origin;
	if (isClockwiseRotation()) {
		origin = Origin::BottomRight;
	}
	else {
		origin = Origin::TopLeft;
	}
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, origin);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, origin);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CircularStroke::draw(const Vector2& position,
						  const int startDraw,
						  const int endDraw,
						  const int startDrain,
						  const int endDrain,
						  const Color& background,
						  const Color& foreground,
						  const float scale) const {
	auto outerScale = (startPosition - center).Magnitude() * scale / imageSize + thickness * 0.5f * scale / imageSize;
	outer->Scale(startDraw, startDraw, outerScale, outerScale);
	auto innerScale = (startPosition - center).Magnitude() * scale / imageSize - thickness * 0.5f * scale / imageSize;
	inner->Scale(startDraw, startDraw, innerScale, innerScale);
	float verticalCoverScale = outerScale * imageSize;
	float horizontalCoverScale = innerScale * imageSize;
	// Set based on cw or ccw rotation
	float rotation;
	Easing easing;
	Easing easingReverse;
	if (isClockwiseRotation()) {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition);
		easing = Easing::SineOut;
		easingReverse = Easing::SineIn;
		horizontalCoverScale = outerScale * imageSize;
		verticalCoverScale = innerScale * imageSize;
	}
	else {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
		easing = Easing::SineIn;
		easingReverse = Easing::SineOut;
		verticalCoverScale = outerScale * imageSize;
		horizontalCoverScale = innerScale * imageSize;
	}
	outer->Rotate(startDraw, startDraw, rotation, rotation);
	inner->Rotate(startDraw, startDraw, rotation, rotation);
	horizontalCover->Rotate(startDraw, startDraw, rotation, rotation);
	verticalCover->Rotate(startDraw, startDraw, rotation, rotation);
	const auto endMove = position + endPosition * scale;
	const auto originalPosition = startPoint->position;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, easingReverse);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, easing);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, easing);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, easingReverse);
	}
	horizontalCover->ScaleVector(startDraw, endDraw, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), easing);
	verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), easingReverse);
	const auto thicknessScale = thickness * scale / imageSize;
	startPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	endPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	inner->Color(startDraw, endDrain, background, background);
	horizontalCover->Color(startDraw, startDraw, background, background);
	verticalCover->Color(startDraw, startDraw, background, background);
	outer->Color(startDrain, endDrain, foreground, background);
	startPoint->Color(startDrain, endDrain, foreground, background);
	endPoint->Color(startDrain, endDrain, foreground, background);
}