#pragma once
#include "Stroke.hpp"
class PointStroke : public Stroke {
public:
	explicit PointStroke(const Vector2& startPosition);
	float calculateLength() const;
	void draw(const Vector2& position,
			  const int startStroke,
			  const int endStroke,
			  const int drawSpeed,
			  const Color& foreground,
			  const Color& background,
			  const float scale);
};