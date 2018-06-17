#include "EighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
// Manipulate positions to mimic QuarterStroke position
EighthStroke::EighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: QuarterStroke{ setStartPosition(startPosition, endPosition, center), 
					 setEndPosition(startPosition, endPosition, center), 
					 center },
	  startOffset{ setStartOffset(startPosition, center) },
	  offsetPosition{ setOffsetPosition(startPosition, endPosition, center) } {
}
float EighthStroke::calculateLength() const {
	return QuarterStroke::calculateLength() / 2.0f;
}
void EighthStroke::createSprites(const Vector2& position, const float scale) {
	std::string outerPath;
	std::string quarterPath;
	std::string startPath;
	std::string endPath;
	if (startOffset) {
		outerPath = getPath(Path::EighthTop);
		startPath = getPath(Path::Blank);
		endPath = getPath(Path::Circle);
		quarterPath = getPath(Path::EighthBottom);
	}
	else {
		outerPath = getPath(Path::EighthBottom);
		startPath = getPath(Path::Circle);
		endPath = getPath(Path::Blank);
		quarterPath = getPath(Path::EighthTop);
	}
	const auto centerPosition = position + center * scale;
	outer = Storyboard::CreateSprite(outerPath, centerPosition, Layer::Background, Origin::BottomLeft);
	inner = Storyboard::CreateSprite(outerPath, centerPosition, Layer::Background, Origin::BottomLeft);
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
	startPoint = Storyboard::CreateSprite(startPath, centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(endPath, startPoint->position, Layer::Background);
	// Additional covers to hide unneeded QuarterStroke sections
	quarterCover = Storyboard::CreateSprite(quarterPath, centerPosition, Layer::Background, Origin::BottomLeft);
	pointCover = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + offsetPosition * scale, Layer::Background);
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
	int startTime;
	int endTime;
	if (startOffset) {
		startTime = startDraw - drawTime;
		endTime = endDraw;
	}
	else {
		startTime = startDraw;
		endTime = endDraw + drawTime;
	}
	QuarterStroke::draw(position,
						startTime,
						endTime,
						startDrain,
						endDrain,
						background,
						foreground,
						scale);
	int pointTime;
	if (startOffset) {
		pointTime = startDraw;
		// To get rid of endPoint when it starts drawing
		endPoint->Color(startDraw, startDraw, background, foreground);
	}
	else {
		pointTime = endDraw;
	}
	quarterCover->Rotate(startTime, startTime, outer->rotation, outer->rotation);
	quarterCover->Scale(startTime, startTime, outer->scale, outer->scale);
	quarterCover->Color(startTime, endDrain, background, background);
	pointCover->Scale(pointTime, pointTime, startPoint->scale, startPoint->scale);
	pointCover->Color(startDrain, endDrain, foreground, background);
}
bool EighthStroke::setStartOffset(const Vector2& startPosition, const Vector2& center) {
	if (startPosition.x != center.x && startPosition.y != center.y) {
		return true;
	}
	else {
		return false;
	}
}
Vector2 EighthStroke::setOffsetPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	if (setStartOffset(startPosition, center)) {
		return startPosition;
	}
	else {
		return endPosition;
	}
}
Vector2 EighthStroke::setStartPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	if (setStartOffset(startPosition, center)) {
		if (setClockwise(startPosition, endPosition)) {
			const auto adjustedPosition = endPosition.RotateAround(center, -Math::pi / 2.0f);
			return adjustedPosition;
		}
		else {
			const auto adjustedPosition = endPosition.RotateAround(center, Math::pi / 2.0f);
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