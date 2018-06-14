#pragma once
#include "Stroke.hpp"
class CircularStroke : public Stroke {
public:
	explicit CircularStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	float calculateLength() const;
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const int endTime,
			  const int drawSpeed,
			  const Color& foreground,
			  const Color& background,
			  const float scale) const;
private:
	const Vector2 center;
	Sprite* outer;
	Sprite* inner;
	Sprite* cover;
	Sprite* startPoint;
	Sprite* endPoint;
};