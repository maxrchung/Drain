#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Walker.hpp"

#include <vector>

class RainWalker : public Walker {
public:
	RainWalker(const std::vector<SpriteCollection> &sprites);

protected:
	SpriteCollection create(const Time& startTime, const Vector2& centerPos);
	void moveCurrent(const Time& startTime, const Time& endTime);
	void moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond);

private:
	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	static constexpr float minScale = 0.01f;
	static constexpr float maxScale = 0.1f;
	static constexpr float offset = 50.0f;
};
