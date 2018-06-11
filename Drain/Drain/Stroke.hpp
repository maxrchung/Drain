#pragma once
#include "Sprite.hpp"
#include "Timing.hpp"
#include "Vector2.hpp"
class Stroke {
public:
	explicit Stroke(const Vector2& startPosition, const Vector2& endPosition);
	virtual float calculateLength() const = 0;
	virtual void createSprites(const Vector2& position, const float scale) = 0;
	virtual void draw(const Vector2& position,
					  const int startStroke,
					  const int endStroke,
					  const int endTime,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) = 0;
	// Thickness of Character stroke represented as a factor of scale
	static constexpr float thickness = 0.1f;
	const Vector2 startPosition;
	const Vector2 endPosition;
protected:
	// Size of sprite images in pixels
	static const int imageSize = 100;
	static const int spawnTime = static_cast<int>(Timing::quarter);
	std::vector<Sprite*> sprites;
};