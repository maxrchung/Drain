#include "CCWQuarterStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWQuarterStroke::CCWQuarterStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center } {
}
void CCWQuarterStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::QuarterOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::QuarterInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = endPosition.Normalize() * (endPosition.Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CCWQuarterStroke::draw(const Vector2& position,
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
	float rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
	outer->Rotate(startDraw, startDraw, rotation, rotation);
	inner->Rotate(startDraw, startDraw, rotation, rotation);
	horizontalCover->Rotate(startDraw, startDraw, rotation, rotation);
	verticalCover->Rotate(startDraw, startDraw, rotation, rotation);
	const auto endMove = position + endPosition * scale;
	const auto originalPosition = startPoint->position;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineIn);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineOut);
	}
	horizontalCover->ScaleVector(startDraw, endDraw, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
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