#include "CCWStartEighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWStartEighthStroke::CCWStartEighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center }, offsetPosition{ endPosition.RotateAround(center, Math::pi / 2.0f) } {
}
void CCWStartEighthStroke::createPoints(const Vector2& position, const float scale) {
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
}
void CCWStartEighthStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::EighthTopOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::EighthTopInner), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = (endPosition - center).Normalize() * ((endPosition - center).Magnitude() + thickness * 0.5f) * scale;
	horizontalCover = Storyboard::CreateSprite(getPath(Path::Pixel), centerPosition + coverPosition, Layer::Background, Origin::TopLeft);
	verticalCover = Storyboard::CreateSprite(getPath(Path::Pixel), centerPosition + coverPosition, Layer::Background, Origin::TopLeft);
}
void CCWStartEighthStroke::draw(const Vector2& position,
								const int startDraw,
								const int endDraw,
								const int startDrain,
								const int endDrain,
								const float scale) const {
	const auto drawTime = endDraw - startDraw;
	const auto startTime = startDraw - drawTime;
	const auto endTime = endDraw;
	scaleInner({ inner }, startTime, startPosition, center, scale);
	scaleOuter({ outer }, startTime, startPosition, center, scale);
	scalePoints({ startPoint, endPoint }, startTime, scale);
	colorBgSprites({ horizontalCover, verticalCover, inner }, startTime, endDrain);
	colorBgSprites({ outer, startPoint, endPoint }, startTime, startDraw);
	colorFgSprites({ outer, startPoint, endPoint }, startDraw, startDrain);
	fadeSprites({ outer }, startDrain, endDrain);
	fadePoints({ startPoint, endPoint }, startDrain, endDrain);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(offsetPosition - center);
	rotateSprites({ outer, inner, horizontalCover, verticalCover }, startTime, rotation);
	float verticalCoverScale = outer->scale * imageSize;
	float horizontalCoverScale = inner->scale * imageSize;
	horizontalCover->ScaleVector(startTime, endTime, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startTime, endTime, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
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
}
void CCWStartEighthStroke::place(const Vector2& position,
								 const int startTime,
								 const int endTime,
								 const float scale,
								 const float drift) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::EighthTopOuter), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::EighthTopInner), centerPosition, Layer::Background, Origin::BottomLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + endPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + endPosition * scale, Layer::Background);
	scaleInner({ inner }, startTime, startPosition, center, scale);
	scaleOuter({ outer }, startTime, startPosition, center, scale);
	scalePoints({ startPoint, endPoint }, startTime, scale);
	colorBgSprites({ inner }, startTime, endTime);
	colorFgSprites({ outer, startPoint, endPoint }, startTime, endTime);
	const auto rotation = Vector2(1.0f, 0.0f).AngleBetween(offsetPosition - center);
	rotateSprites({ outer, inner, }, startTime, rotation);
	placeDrift({ outer, inner, startPoint, endPoint }, startTime, endTime, drift);
}