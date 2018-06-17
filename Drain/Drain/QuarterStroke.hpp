#pragma once
#include "Stroke.hpp"
class QuarterStroke : public Stroke {
public:
	explicit QuarterStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	virtual float calculateLength() const;
	virtual void createSprites(const Vector2& position, const float scale);
	virtual void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const Color& background,
			  const Color& foreground,
			  const float scale) const;
protected:
	static bool setClockwise(const Vector2& startPosition, const Vector2& endPosition);
	const bool clockwise;
	const Vector2 center;
	Sprite* outer;
	Sprite* inner;
	Sprite* horizontalCover;
	Sprite* verticalCover;
	Sprite* startPoint;
	Sprite* endPoint;
};