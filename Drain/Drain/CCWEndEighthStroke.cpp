#include "CCWEndEighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWEndEighthStroke::CCWEndEighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center }, offsetPosition{ startPosition.RotateAround(center, -Math::pi / 2.0f) } {
}
void CCWEndEighthStroke::createPoints(const Vector2& position, const float scale) {
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
	pointCover = Storyboard::CreateSprite(getPath(Path::Circle), position + endPosition * scale, Layer::Background);
}
void CCWEndEighthStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::EighthBottomOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::EighthBottomInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = offsetPosition.Normalize() * (offsetPosition.Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), position + coverPosition, Layer::Background, Origin::TopLeft);
	// Additional covers to hide unneeded QuarterStroke sections
	quarterCover = Storyboard::CreateSprite(getPath(Path::EighthTopInner), centerPosition, Layer::Background, Origin::BottomLeft);
}
void CCWEndEighthStroke::draw(const Vector2& position,
						const int startDraw,
						const int endDraw,
						const int startDrain,
						const int endDrain,
						const float scale) const {
	const auto drawTime = endDraw - startDraw;
	const auto startTime = startDraw;
	const auto endTime = endDraw + drawTime;
	scaleInner({ inner }, startTime, startPosition, center, scale);
	scaleOuter({ outer, quarterCover }, startTime, startPosition, center, scale);
	scalePoints({ startPoint, endPoint }, startTime, scale);
	pointCover->Scale(endDraw, endDraw, endPoint->scale, endPoint->scale);
	colorBgSprites({ horizontalCover, verticalCover }, startTime, startTime);
	colorBgSprites({ inner, quarterCover }, startTime, endDrain);
	colorFgSprites({ pointCover }, endDraw, endDraw);
	fadeSprites({ outer, startPoint, pointCover }, startDrain, endDrain);
	fadeSprites({ endPoint }, endDraw, endDraw);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
	rotateSprites({ outer, inner, horizontalCover, verticalCover, quarterCover }, startTime, rotation);
	const auto verticalCoverScale = outer->scale * imageSize;
	const auto horizontalCoverScale = inner->scale * imageSize;
	horizontalCover->ScaleVector(startTime, endTime, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startTime, endTime, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
	const auto endMove = position + offsetPosition * scale;
	const auto originalPosition = startPoint->position;
	// Set easing based on how point is moving
	if (startPosition.x > endPosition.x && startPosition.y > endPosition.y ||
		startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startTime, endTime, originalPosition.x, endMove.x, Easing::SineOut);
		endPoint->MoveY(startTime, endTime, originalPosition.y, endMove.y, Easing::SineIn);
	}
	else if (startPosition.x < endPosition.x && startPosition.y > endPosition.y ||
			 startPosition.x > endPosition.x && startPosition.y < endPosition.y) {
		endPoint->MoveX(startTime, endTime, originalPosition.x, endMove.x, Easing::SineIn);
		endPoint->MoveY(startTime, endTime, originalPosition.y, endMove.y, Easing::SineOut);
	}
}