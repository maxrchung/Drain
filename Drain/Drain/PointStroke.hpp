#pragma once
#include "Stroke.hpp"
class PointStroke : public Stroke {
public:
	explicit PointStroke(const Vector2& start);
	float calculateLength() const;
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int strokeStart,
			  const int strokeEnd,
			  const int drawSpeed,
			  const Color& foreground,
			  const Color& background,
			  const float scale);
};