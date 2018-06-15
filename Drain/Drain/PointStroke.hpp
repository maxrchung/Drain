#pragma once
#include "Stroke.hpp"
class PointStroke : public Stroke {
public:
	explicit PointStroke(const Vector2& startPosition);
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
};