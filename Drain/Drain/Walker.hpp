#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <vector>

class Walker {
public:
	Walker(const std::vector<SpriteCollection>& sprites);
	// spawnsPerSecond: How many SpriteCollection to spawn per second
	void walk(const Time& startTime, const Time& endTime, const float spawnsPerSecond);

	std::vector<SpriteCollection> sprites;

protected:
	virtual SpriteCollection create(const Time& startTime, const Vector2& centerPos) = 0;
	//move sprites from generator
	virtual void moveCurrent(const Time& startTime, const Time& endTime) = 0;
	//move the sprites
	virtual void moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond) = 0;

	// Helper to generate a random float
	static float generateRandomFloat(const float min, const float max);
	// Helper to check if a point is in the screen
	static bool isInScreen(const Vector2& point);
	//given a line between the Vector2s b and a, find the point at
	//which it crosses the screen
	static Vector2 findEndPoint(const Vector2& startPosition, const float offset);

private:
	//size in pixels
	static const int SPRITE_SIZE = 100;
};
