#include "CCWEndEighthStroke.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
CCWEndEighthStroke::CCWEndEighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: CircularStroke{ startPosition, endPosition, center }, offsetPosition{ startPosition.RotateAround(center, -Math::pi / 2.0f) } {
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
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + startPosition * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), startPoint->position, Layer::Background);
	pointCover = Storyboard::CreateSprite(getPath(Path::Circle), centerPosition + endPosition * scale, Layer::Background);
}
void CCWEndEighthStroke::draw(const Vector2& position,
						const int startDraw,
						const int endDraw,
						const int startDrain,
						const int endDrain,
						const Color& background,
						const Color& foreground,
						const float scale) const {
	const auto drawTime = endDraw - startDraw;
	const auto startTime = startDraw;
	const auto endTime = endDraw + drawTime;
	const auto outerScale = (startPosition - center).Magnitude() * scale / imageSize + thickness * 0.5f * scale / imageSize;
	outer->Scale(startTime, startTime, outerScale, outerScale);
	const auto innerScale = (startPosition - center).Magnitude() * scale / imageSize - thickness * 0.5f * scale / imageSize;
	inner->Scale(startTime, startTime, innerScale, innerScale); 
	const auto verticalCoverScale = outerScale * imageSize;
	const auto horizontalCoverScale = innerScale * imageSize;
	float rotation = Vector2(1.0f, 0.0f).AngleBetween(startPosition);
	outer->Rotate(startTime, startTime, rotation, rotation);
	inner->Rotate(startTime, startTime, rotation, rotation);
	horizontalCover->Rotate(startTime, startTime, rotation, rotation);
	verticalCover->Rotate(startTime, startTime, rotation, rotation);
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
	horizontalCover->ScaleVector(startTime, endTime, Vector2(horizontalCoverScale, horizontalCoverScale), Vector2(0, horizontalCoverScale), Easing::SineIn);
	verticalCover->ScaleVector(startTime, endTime, Vector2(verticalCoverScale, verticalCoverScale), Vector2(verticalCoverScale, 0), Easing::SineOut);
	const auto thicknessScale = thickness * scale / imageSize;
	startPoint->Scale(startTime, startTime, thicknessScale, thicknessScale);
	endPoint->Scale(startTime, startTime, thicknessScale, thicknessScale);
	inner->Color(startDraw, endDrain, background, background);
	horizontalCover->Color(startDraw, startDraw, background, background);
	verticalCover->Color(startDraw, startDraw, background, background);
	outer->Color(startDrain, endDrain, foreground, background);
	startPoint->Color(startDrain, endDrain, foreground, background);
	endPoint->Color(endDraw, endDraw, foreground, background);
	quarterCover->Rotate(endDraw, endDraw, outer->rotation, outer->rotation);
	quarterCover->Scale(endDraw, endDraw, outer->scale, outer->scale);
	quarterCover->Color(endDraw, endDrain, background, background);
	pointCover->Scale(endDraw, endDraw, startPoint->scale, startPoint->scale);
	pointCover->Color(startDrain, endDrain, foreground, background);
}