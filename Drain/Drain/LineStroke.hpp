#pragma once
#include "Stroke.hpp"
class LineStroke : public Stroke {
public:
	explicit LineStroke(const Vector2& start, const Vector2& end);
	float calculateLength() const;
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startStroke,
			  const int endStroke,
			  const int endTime,
			  const int drawSpeed,
			  const Color& foreground,
			  const Color& background,
			  const float scale);
private:
	Sprite* line;
	Sprite* startPoint;
	Sprite* endPoint;
};