#pragma once
#include "Color.hpp"
#include "RandomRange.hpp"
#include "Stroke.hpp"
#include "Vector2.hpp"
#include <memory>
#include <unordered_map>
class Character {
public:
	const std::vector<std::unique_ptr<Stroke>>& getStrokes() const;
	explicit Character(const char character);
	float calculateTopToCenter(const float scale) const;
	float calculateLeftToCenter(const float scale) const;
	float calculateHeight(const float scale) const;
	float calculateWidth(const float scale) const;
	void draw(const Vector2& position,
			  const int startTime,
			  const int endTime,
			  const float scale) const;
	void place(const Vector2& position,
			   const int startTime,
			   const int endTime,
			   const float scale) const;
private:
	static std::vector<std::unique_ptr<Stroke>> createStrokes(const char character);
	static const int drawBuffer = Timing::half;
	static const int drainTime = Timing::whole;
	static const RandomRange drift;
	static const RandomRange driftNegative;
	void createPoints(const Vector2& position, const float scale) const;
	void createSprites(const Vector2& position, const float scale) const;
	std::vector<std::unique_ptr<Stroke>> strokes;
	float calculateLength() const;
};