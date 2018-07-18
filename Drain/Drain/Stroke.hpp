#pragma once
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "Timing.hpp"
#include "Vector2.hpp"
class Stroke {
public:
	virtual float calculateLength() const = 0;
	virtual Vector2 getEndPosition() const = 0;
	virtual Vector2 getStartPosition() const = 0;
	virtual void createPoints(const Vector2& position, const float scale) = 0;
	virtual void createSprites(const Vector2& position, const float scale) = 0;
	virtual void draw(const Vector2& position,
					  const int startDraw,
					  const int endDraw,
					  const int startDrain,
					  const int endDrain,
					  const float scale) const = 0;
	virtual void place(const Vector2& position,
					   const int startTime,
					   const int endTime,
					   const float scale) = 0;
	// Thickness of Character stroke represented as a factor of scale
	static constexpr float thickness = 0.14f;
protected:
	// Helper static functions used to consolidate similar pieces of code
	static void colorBgSprites(const std::vector<Sprite*>& sprites, const int startDraw, const int endDraw);
	static void colorFgSprites(const std::vector<Sprite*>& sprites, const int startDraw, const int endDraw);
	static void fadeSprites(const std::vector<Sprite*>& sprites, const int startDrain, const int endDrain);
	static void fadePoints(const std::vector<Sprite*>& sprites, const int startDrain, const int endDrain);
	static void hideSprites(const std::vector<Sprite*>& sprites, const int endDraw);
	static void rotateSprites(const std::vector<Sprite*>& sprites, const int startDraw, const float rotation);
	static void scaleInner(const std::vector<Sprite*>& sprites, const int startDraw, const Vector2& startPosition, const Vector2& center, const float scale);
	static void scaleOuter(const std::vector<Sprite*>& sprites, const int startDraw, const Vector2& startPosition, const Vector2& center, const float scale);
	static void scalePoints(const std::vector<Sprite*>& points, const int startDraw, const float scale);
	// Size of sprite images in pixels
	static const int imageSize = 100;
	static const RandomRange pointScale;
};
