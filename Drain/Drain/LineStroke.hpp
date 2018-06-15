#pragma once
#include "Stroke.hpp"
class LineStroke : public Stroke {
public:
	explicit LineStroke(const Vector2& start, const Vector2& end);
	float calculateLength() const;
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const Color& background,
			  const Color& foreground,
			  const float scale) const;
private:
	Sprite* line;
	Sprite* startPoint;
	Sprite* endPoint;
};