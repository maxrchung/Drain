#pragma once
#include "Stroke.hpp"
class BlankStroke : public Stroke {
public:
	explicit BlankStroke();
	float calculateLength() const;
	Vector2 getEndPosition() const;
	Vector2 getStartPosition() const;
	void createPoints(const Vector2& position, const float scale);
	void createSprites(const Vector2& position, const float scale);
	void draw(const Vector2& position,
			  const int startDraw,
			  const int endDraw,
			  const int startDrain,
			  const int endDrain,
			  const float scale) const;
	void place(const Vector2& position,
			   const int startTime,
			   const int endTime,
			   const float scale);
};