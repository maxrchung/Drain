#pragma once
#include "CircularStroke.hpp"
class CWQuarterStroke : public CircularStroke {
public:
	explicit CWQuarterStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const Color& background,
			  const Color& foreground,
			  const float scale) const;
};