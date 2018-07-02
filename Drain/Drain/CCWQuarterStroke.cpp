#include "CCWQuarterStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWQuarterStroke::CCWQuarterStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center } {
}
void CCWQuarterStroke::createPoints(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CCWQuarterStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::QuarterOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::QuarterInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = endPosition.Normalize() * (endPosition.Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
}
void CCWQuarterStroke::draw(const Vector2& position,
							const int startDraw,
							const int endDraw,
							const int startDrain,
							const int endDrain,
							const float scale) const {
	scaleInner({ inner }, startDraw, startPosition, center, scale);
	scaleOuter({ outer }, startDraw, startPosition, center, scale);
	scalePoints({ startPoint, endPoint }, startDraw, scale);
	colorBgSprites({ horizontalCover, verticalCover }, startDraw, startDraw);
	colorBgSprites({ inner }, startDraw, endDrain);
	fadeSprites({ outer, startPoint, endPoint }, startDrain, endDrain);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
	rotateSprites({ outer, inner, horizontalCover, verticalCover }, startDraw, rotation);
	const auto verticalCoverScale = outer->scale * imageSize;
	const auto horizontalCoverScale = inner->scale * imageSize;
	horizontalCover->ScaleVector(startDraw, endDraw, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startDraw, endDraw, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
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
}