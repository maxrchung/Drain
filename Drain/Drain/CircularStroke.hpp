#pragma once
#include "Stroke.hpp"
class CircularStroke : public Stroke {
public:
	explicit CircularStroke(const Vector2& start, const Vector2& end, const Vector2& center);
	float calculateLength() const;
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int strokeStart,
			  const int strokeEnd,
			  const int drawSpeed,
			  const Color& foreground,
			  const Color& background,
			  const float scale);
private:
	const Vector2 center;
};