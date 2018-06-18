#pragma once
#include "Stroke.hpp"
class CircularStroke : public Stroke {
public:
	explicit CircularStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	static std::unique_ptr<CircularStroke> create(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	float calculateLength() const;
	virtual void createSprites(const Vector2& position, const float scale) = 0;
	virtual void draw(const Vector2& position,
					  const int startDraw,
					  const int endDraw,
					  const int startDrain,
					  const int endDrain,
					  const Color& background,
					  const Color& foreground,
					  const float scale) const = 0;
protected:
	static bool isClockwise(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	static bool isStartOffset(const Vector2& startPosition, const Vector2& center);
	static bool isEndOffset(const Vector2& endPosition, const Vector2& center);
	const Vector2 center;
	Sprite* outer;
	Sprite* inner;
	Sprite* horizontalCover;
	Sprite* verticalCover;
	Sprite* startPoint;
	Sprite* endPoint;
};