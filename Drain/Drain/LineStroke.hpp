#pragma once
#include "Stroke.hpp"
class LineStroke : public Stroke {
public:
	explicit LineStroke(const Vector2& start, const Vector2& end);
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
private:
	const Vector2 endPosition;
	const Vector2 startPosition;
	Sprite* line;
	Sprite* startPoint;
	Sprite* endPoint;
};