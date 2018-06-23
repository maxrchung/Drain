#pragma once
#include "Color.hpp"
#include "Stroke.hpp"
#include "Vector2.hpp"
#include <memory>
class Character {
public:
	explicit Character(const char character);
	// Cannot assume that center will always be width / 2, e.g. c character
	float calculateCenter(const float scale) const;
	float calculateWidth(const float scale) const;
	void draw(const Vector2& position,
			  const int startTime,
			  const int endTime,
			  const Color& background,
			  const Color& foreground,
			  const float scale) const;
private:
	static std::vector<std::unique_ptr<Stroke>> createStrokes(const char character);
	static const int drawBuffer = Timing::half;
	static const int drainTime = Timing::half;
	void createSprites(const Vector2& position, const float scale) const;
	std::vector<std::unique_ptr<Stroke>> strokes;
	float calculateLength() const;
};