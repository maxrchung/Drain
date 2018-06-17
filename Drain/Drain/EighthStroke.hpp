#pragma once
#include "QuarterStroke.hpp"
class EighthStroke : public QuarterStroke {
public:
	explicit EighthStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
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
	static bool setStartOffset(const Vector2& startPosition, const Vector2& center);
	static Vector2 setStartPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	static Vector2 setEndPosition(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center);
	// Flag for denoting offset
	// If true then start needs to be offset
	// If false then end needs to be  offset
	const bool startOffset;
};