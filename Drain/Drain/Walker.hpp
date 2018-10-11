#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"

#include <vector>


class Walker {
public:
	Walker(const std::vector<SpriteCollection> &sprites);
	virtual void walk(float distance, Time startTime, Time endTime, float density);

	std::vector<SpriteCollection> sprites;

protected:
	float w_rand(float min, float max);

	//check if the given 3d coordinate is on screen
	virtual bool inScreen(Vector2 a);

	//given a line between the Vector2s b and a, find the point at
	//which is crosses the screen
	virtual Vector2 findProjection(Vector2 a, Vector2 b);

	//move sprites from RainGenerator
	virtual void moveCurrent(float distance, Time startTime, Time endTime);

	//move the sprites
	virtual void moveSprites(float distance, Time startTime, Time endTime, float density);

	virtual SpriteCollection create(const Time& startTime, const Vector2& centerPos, const float scale);

	//size in pixels
	const uint8_t sprite_size = 100;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	const float min_scale = 0.01;
	const float max_scale = 0.1;

	const float sizeScale = 1;

	//sizes of the raindrop
	const float minSize = 10;
	const float maxSize = 100;
};
