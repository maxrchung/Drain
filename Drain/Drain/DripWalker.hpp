#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Walker.hpp"

#include <vector>

class DripWalker : public Walker {
public:
	DripWalker(const std::vector<SpriteCollection> &sprites);

protected:
	static Vector2 findDripEndPoint(const Vector2& startPosition, const float offset);

	SpriteCollection create(const Time& startTime, const Vector2& centerPos);
	void moveCurrent(const Time& startTime, const Time& endTime);
	void moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond);
private:
	static void specialScale(SpriteCollection& collection, const int startTime, const int endTime, const Vector2& startPos, const Vector2& endPos, const float scaleTo, const Easing& easing = Easing::Linear, const int precision = 3);
	static constexpr float COLUMN_PIXEL_SIZE = 100.0f;
	static constexpr float OFFSET = 70.0f;
};