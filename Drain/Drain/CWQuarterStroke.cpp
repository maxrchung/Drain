#include "CWQuarterStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CWQuarterStroke::CWQuarterStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center } {
}
void CWQuarterStroke::createPoints(const Vector2& position, const float scale) {
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CWQuarterStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::QuarterOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::QuarterInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = (endPosition - center).Normalize() * ((endPosition - center).Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), centerPosition + coverPosition, Layer::Background, Origin::BottomRight);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), centerPosition + coverPosition, Layer::Background, Origin::BottomRight);
}
void CWQuarterStroke::draw(const Vector2& position,
						   const int startDraw,
						   const int endDraw,
						   const int startDrain,
						   const int endDrain,
						   const float scale) const {
	scalePoints({ startPoint, endPoint }, startDraw, scale);
	scaleOuter({ outer }, startDraw, startPosition, center, scale);
	scaleInner({ inner }, startDraw, startPosition, center, scale);
	colorBgSprites({ inner }, startDraw, endDrain);
	colorBgSprites({ horizontalCover, verticalCover }, startDraw, endDrain);
	colorFgSprites({ outer, startPoint, endPoint }, startDraw, startDrain);
	fadeSprites({ outer }, startDrain, endDrain);
	fadePoints({ startPoint, endPoint }, startDrain, endDrain);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition - center);
	rotateSprites({ outer, inner, horizontalCover, verticalCover }, startDraw, rotation);
	const auto verticalCoverScale = inner->scale * imageSize;
	const auto horizontalCoverScale = outer->scale * imageSize;
	horizontalCover->ScaleVector(startDraw, endDraw, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineOut);
	verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineIn);
	const auto endMove = position + endPosition * scale;
	const auto originalPosition = startPoint->position;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineOut);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startDraw, endDraw, originalPosition.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startDraw, endDraw, originalPosition.y, endMove.y, Easing::SineIn);
	}
}
void CWQuarterStroke::place(const Vector2& position,
							const int startTime,
							const int endTime,
							const float scale,
							const float drift) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::QuarterOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::QuarterInner), centerPosition, Layer::Background, Origin::BottomLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + endPosition * scale, Layer::Background);
	scalePoints({ startPoint, endPoint }, startTime, scale);
	scaleOuter({ outer }, startTime, startPosition, center, scale);
	scaleInner({ inner }, startTime, startPosition, center, scale);
	colorBgSprites({ inner }, startTime, endTime);
	colorFgSprites({ outer, startPoint, endPoint }, startTime, endTime);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(endPosition - center);
	rotateSprites({ outer, inner, }, startTime, rotation);
	placeDrift({ outer, inner, startPoint, endPoint }, startTime, endTime, drift);
}