#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Walker.hpp"

#include <vector>

class Splatter_walker : public Walker {
public:
	Splatter_walker(const std::vector<SpriteCollection> &sprites);

protected:
	SpriteCollection create(const Time& startTime, const Vector2& centerPos, const float scale);

	const uint8_t sprite_size = 200;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	const float min_scale = 0.01;
	const float max_scale = 0.1;

	const float sizeScale = 1;

	const float minSize = 10;
	const float maxSize = 100;
};
