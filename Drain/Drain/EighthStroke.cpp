#include "EighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
// Manipulate positions to mimic QuarterStroke position
EighthStroke::EighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: QuarterStroke{ setStartPosition(startPosition, endPosition, center), 
					 setEndPosition(startPosition, endPosition, center), 
					 center }, 
	  startOffset{ setStartOffset(startPosition, center) } {
}
float EighthStroke::calculateLength() const {
	return QuarterStroke::calculateLength() / 2.0f;
}
void EighthStroke::createSprites(const Vector2& position, const float scale) {
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(getPath(Path::Eighth), centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(getPath(Path::Eighth), centerPosition, Layer::Background, Origin::BottomLeft);
	const auto coverPosition = endPosition.Normalize() * (endPosition.Magnitude() + thickness * 0.5f) * scale;
	Origin origin;
	if (clockwise) {
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
void EighthStroke::draw(const Vector2& position,
						const int startDraw,
						const int endDraw,
						const int startDrain,
						const int endDrain,
						const Color& background,
						const Color& foreground,
						const float scale) const {
	const auto drawTime = endDraw - startDraw;
	int startTime = startDraw;
	int endTime = endDraw;
	if (startOffset) {
		startTime -= drawTime;
	}
	else {
		endTime = startDraw + drawTime / 2.0f;
	}
	QuarterStroke::draw(position,
						startTime,
						endTime,
						startDrain,
						endDrain,
						background,
						foreground,
						scale);
}
bool EighthStroke::setStartOffset(const Vector2& startPosition, const Vector2& center) {
	if (startPosition.x == center.x || startPosition.y == center.y) {
		return true;
	}
	else {
		return false;
	}
}
Vector2 EighthStroke::setStartPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	if (setStartOffset(startPosition, center)) {
		if (setClockwise(startPosition, endPosition)) {
			const auto adjustedPosition = endPosition.RotateAround(center, Math::pi / 2.0f);
			return adjustedPosition;
		}
		else {
			const auto adjustedPosition = endPosition.RotateAround(center, -Math::pi / 2.0f);
			return adjustedPosition;
		}
	}
	else {
		return startPosition;
	}
}
Vector2 EighthStroke::setEndPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	if (!setStartOffset(startPosition, center)) {
		if (setClockwise(startPosition, endPosition)) {
			const auto adjustedPosition = startPosition.RotateAround(center, Math::pi / 2.0f);
			return adjustedPosition;
		}
		else {
			const auto adjustedPosition = startPosition.RotateAround(center, -Math::pi / 2.0f);
			return adjustedPosition;
		}
	}
	else {
		return endPosition;
	}
}