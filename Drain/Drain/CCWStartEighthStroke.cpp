#include "CCWStartEighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWStartEighthStroke::CCWStartEighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center }, offsetPosition{ endPosition.RotateAround(center, Math::pi / 2.0f) } {
}
void CCWStartEighthStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::EighthTopOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::EighthTopInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = endPosition.Normalize() * (endPosition.Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	// Additional covers to hide unneeded QuarterStroke sections
	quarterCover = Storyboard::CreateSprite(getPath(Path::EighthBottomInner), centerPosition, Layer::Background, Origin::BottomLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CCWStartEighthStroke::draw(const Vector2& position,
						const int startDraw,
						const int endDraw,
						const int startDrain,
						const int endDrain,
						const Color& background,
						const Color& foreground,
						const float scale) const {
	const auto drawTime = endDraw - startDraw;
	const auto startTime = startDraw - drawTime;
	const auto endTime = endDraw;
	auto outerScale = ((offsetPosition - center).Magnitude() * scale) / imageSize + (thickness * 0.5f * scale) / imageSize;
	outer->Scale(startTime, startTime, outerScale, outerScale);
	auto innerScale = ((offsetPosition - center).Magnitude() * scale) / imageSize - (thickness * 0.5f * scale) / imageSize;
	inner->Scale(startTime, startTime, innerScale, innerScale);
	float verticalCoverScale = outerScale * imageSize;
	float horizontalCoverScale = innerScale * imageSize;
	horizontalCover->ScaleVector(startTime, endTime, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startTime, endTime, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
	const auto thicknessScale = thickness * scale / imageSize;
	startPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	endPoint->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(offsetPosition);
	outer->Rotate(startTime, startTime, rotation, rotation);
	inner->Rotate(startTime, startTime, rotation, rotation);
	horizontalCover->Rotate(startTime, startTime, rotation, rotation);
	verticalCover->Rotate(startTime, startTime, rotation, rotation);
	const auto endMove = position + endPosition * scale;
	const auto originalPosition = position + offsetPosition * scale;
	// Set easing based on how point is moving
	if (offsetPosition.x > endPosition.x && offsetPosition.y > endPosition.y ||
		offsetPosition.x < endPosition.x && offsetPosition.y < endPosition.y) {
		endPoint->MoveX(startTime, endTime, originalPosition.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startTime, endTime, originalPosition.y, endMove.y, Easing::SineIn);
	}
	else if (offsetPosition.x < endPosition.x && offsetPosition.y > endPosition.y ||
			 offsetPosition.x > endPosition.x && offsetPosition.y < endPosition.y) {
		endPoint->MoveX(startTime, endTime, originalPosition.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startTime, endTime, originalPosition.y, endMove.y, Easing::SineOut);
	}
	inner->Color(startDraw, endDrain, background, background);
	horizontalCover->Color(startDraw, startDraw, background, background);
	verticalCover->Color(startDraw, startDraw, background, background);
	outer->Color(startDrain, endDrain, foreground, background);
	startPoint->Color(startDrain, endDrain, foreground, background);
	endPoint->Color(startDraw, startDraw, background, foreground);
	endPoint->Color(startDrain, endDrain, foreground, background);
	quarterCover->Rotate(startTime, startTime, outer->rotation, outer->rotation);
	quarterCover->Scale(startTime, startTime, outer->scale, outer->scale);
	quarterCover->Color(startTime, endDrain, background, background);
}