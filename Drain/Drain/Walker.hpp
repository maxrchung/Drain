#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <vector>

class Walker {
public:
	Walker(const std::vector<SpriteCollection>& sprites);
	void walk(const float distance, const Time& startTime, const Time& endTime, const float density);

	std::vector<SpriteCollection> sprites;

protected:
	// Helper to generate a random float
	static float generateRandomFloat(const float min, const float max);
	// Helper to check if a point is in the screen
	static bool isInScreen(const Vector2& point);
	//given a line between the Vector2s b and a, find the point at
	//which it crosses the screen
	static Vector2 findEndPoint(const Vector2& b);

	//move sprites from RainGenerator
	void moveCurrent(const Time& startTime, const Time& endTime);

	//move the sprites
	void moveSprites(const float distance, const Time& startTime, const Time& endTime, const float density);

	virtual SpriteCollection create(const Time& startTime, const Vector2& centerPos, const float scale) = 0;

private:
	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	static constexpr float minScale = 0.01f;
	static constexpr float maxScale = 0.1f;
	static constexpr float sizeScale = 1.0f;

	//size in pixels
	static const int SPRITE_SIZE = 100;
};
