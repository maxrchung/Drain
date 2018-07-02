#pragma once
#include "CircularStroke.hpp"
class CCWEndEighthStroke : public CircularStroke {
public:
	explicit CCWEndEighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	void createPoints(const Vector2& position, const float scale);
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const float scale) const;
private:
	const Vector2 offsetPosition;
	Sprite* quarterCover;
	Sprite* pointCover;
};