#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Walker.hpp"

#include <vector>

class Splatter_walker : public Walker {
public:
	void walk(float distance, Time startTime, Time endTime, float density);

private:
	float w_rand(float min, float max);

        void moveCurrent(float distance, Time startTime, Time endTime);

	//move the sprites
	void moveSprites(float distance, Time startTime, Time endTime, float density);

	SpriteCollection create(void);

	bool inScreen(Vector2 a);

	//given a line between the Vector2s b and a, find the point at
	//which is crosses the screen
	Vector2 findProjection(Vector2 a, Vector2 b);

	const uint8_t sprite_size = 200;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	const float min_scale = 0.01;
	const float max_scale = 0.1;

	const float sizeScale = 1;

	const float minSize = 10;
	const float maxSize = 100;
};
