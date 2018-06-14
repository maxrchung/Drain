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
	cover = Storyboard::CreateSprite(getPath(Path::Pixel), coverPosition, Layer::Background, Origin::TopLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CircularStroke::drain(const Vector2& position,
						   const int startStroke,
						   const int endStroke,
						   const int endTime,
						   const int drawSpeed,
						   const Color& foreground,
						   const Color& background,
						   const float scale) const {
}
void CircularStroke::draw(const Vector2& position,
						  const int startStroke,
						  const int endStroke,
						  const int endTime,
						  const int drawSpeed,
						  const Color& foreground,
						  const Color& background,
						  const float scale) const {
	auto outerScale = (startPosition - center).Magnitude() * scale / imageSize + thickness * 0.5f * scale / imageSize;
	outer->Scale(startStroke, startStroke, outerScale, outerScale);
	auto innerScale = (startPosition - center).Magnitude() * scale / imageSize - thickness * 0.5f * scale / imageSize;
	inner->Scale(startStroke, startStroke, innerScale, innerScale);
	auto coverScale = outerScale * imageSize;
	const auto angleBetween = startPosition.AngleBetween(endPosition);
	// Set rotation and cover scale based on cw or ccw rotation
	float rotation;
	if (angleBetween > 0) {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition);
		cover->ScaleVector(startStroke, endStroke, Vector2(coverScale, 0), Vector2(coverScale, coverScale), Easing::SineOut);
	}
	else {
		rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
		cover->ScaleVector(startStroke, endStroke, Vector2(coverScale, coverScale), Vector2(coverScale, 0), Easing::SineOut);
	}
	outer->Rotate(startStroke, endTime, rotation, rotation);
	inner->Rotate(startStroke, endTime, rotation, rotation);
	cover->Rotate(startStroke, endTime, rotation, rotation);
	outer->Color(startStroke, startStroke, foreground, foreground);
	inner->Color(startStroke, startStroke, background, background);
	const auto thicknessScale = thickness * scale / imageSize;
	startPoint->Scale(startStroke - spawnTime, startStroke, 0, thicknessScale);
	startPoint->Scale(startStroke, startStroke, thicknessScale, thicknessScale);
	startPoint->Scale(endTime, endTime + drawSpeed + spawnTime, thicknessScale, 0);
	endPoint->Scale(startStroke - spawnTime, startStroke, 0, thicknessScale);
	endPoint->Scale(startStroke, startStroke, thicknessScale, thicknessScale);
	endPoint->Scale(endTime, endTime + drawSpeed + spawnTime, thicknessScale, 0);
	const auto endMove = position + endPosition * scale;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startStroke, endStroke, startPoint->position.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startStroke, endStroke, startPoint->position.y, endMove.y, Easing::SineIn);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startStroke, endStroke, startPoint->position.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startStroke, endStroke, startPoint->position.y, endMove.y, Easing::SineOut);
	}
}